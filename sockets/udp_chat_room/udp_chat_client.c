#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include <locale.h>
#include <getopt.h>

#include "chat.h"

#define DEFAULT_IP "127.0.0.1"
const char* serv_ip = DEFAULT_IP;
uint16_t serv_port = 8081;

WINDOW* main_win;
WINDOW *chat_win, *chat_wbox;
WINDOW *input_win, *input_wbox;

LIST_HEAD(msg_list_head);
struct list_head* iter;

uname_t current_name;
uint16_t current_uid;
struct user_t* current_user() {
  return user_list[current_uid];
}

char sbuf[BUFSIZ];
char* req_buf = sbuf + sizeof(struct chat_package);
char rbuf[BUFSIZ];
struct chat_package* res_pkg = (struct chat_package*)rbuf;
char* res_data = rbuf + sizeof(struct chat_package);

int sockfd;
struct sockaddr_in serv_addr;

void setup_socket(int argc, char* argv[]) {
  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd < 0) {
    fprintf(stderr, "create socket error\n");
    exit(-1);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(serv_port);
  serv_addr.sin_addr.s_addr = inet_addr(serv_ip);
  debug_log("connecting %s:%d as %s\n", serv_ip, serv_port, current_name);
}

void make_udp_req(uint8_t type, size_t sz) {
  struct chat_package pkg = {
      .proto = CHAT_PACKAGE_PROTO,
      .type = type,
      .size = sz,
      .checksum = 0,
  };

  memcpy(sbuf, &pkg, sizeof pkg);
  sendto(sockfd, sbuf, sz + sizeof pkg, 0, (struct sockaddr*)&serv_addr,
         sizeof serv_addr);
}

void wait_udp_res() { recvfrom(sockfd, rbuf, sizeof rbuf, 0, NULL, NULL); }

void mk_req_msg(uint32_t msg_id) {
  ((struct req_get_msg*)req_buf)->msg_id = msg_id;
  make_udp_req(Type_REQ_GET, sizeof(struct req_get_msg));
}

struct msg_list* mk_res_msg_node() {
  if (res_pkg->proto != CHAT_PACKAGE_PROTO || res_pkg->type != Type_RES_MSG) {
    return NULL;
  }
  struct msg_t msg;
  memcpy(&msg, res_data, sizeof(struct msg_t));
  char* tmp_buf = res_data + offsetof(struct msg_t, msg);
  char* msg_buf = (char*)malloc(msg.msg_len + 1);
  memcpy(msg_buf, tmp_buf, msg.msg_len);
  msg_buf[msg.msg_len] = '\0';
  msg.msg = msg_buf;

  struct msg_list* msg_node = (struct msg_list*)malloc(sizeof(struct msg_list));
  msg_node->msg = msg;
  return msg_node;
}

struct user_t* get_user_or_req(uint16_t uid) {
  if (is_valid_uid(uid)) {
    return user_list[uid];
  }
  if (uid > 0 && uid < MAX_USER_SIZE) {
    ((struct req_get_user*)req_buf)->uid = uid;
    make_udp_req(Type_REQ_USER, sizeof(struct req_get_user));
    uint32_t i = 10000;
    while (i-- > 0)
      ;

    if (is_valid_uid(uid)) {
      return user_list[uid];
    }
  }
  return NULL;
}

void setup_connection() {
  struct req_join_user join;
  strcpy(join.name, current_name);

  memcpy(req_buf, &join, sizeof join);
  make_udp_req(Type_REQ_JOIN, sizeof join);
  debug_log("waiting for reply...\n");
  wait_udp_res();
  if (res_pkg->type != Type_RES_JOIN) {
    debug_log("setup connection\n");
    exit(-1);
  }

  struct res_join_user* res_user = (struct res_join_user*)res_data;
  if (res_user->flag != 1) {
    debug_log("connect error\n");
    exit(-1);
  }

  current_uid = res_user->uid;

  struct user_t* user = (struct user_t*)malloc(sizeof(struct user_t));
  user->uid = current_uid;
  strcpy(user->name, current_name);
  user->join_time = res_user->join_time;

  debug_log("connected to chat room\nuid(%s): %d\n", current_name, current_uid);

  uint32_t last_id = res_user->last_msg_id;
  // 获取前 10 条消息
  for (uint32_t i = last_id; i > (last_id > 10 ? last_id - 10 : 0); i--) {
    mk_req_msg(i);
    wait_udp_res();
    struct msg_list* node = mk_res_msg_node();
    if (node != NULL) {
      list_add(&node->list, &msg_list_head);
    }
  }
}

void refresh_chat_messages() {
  wclear(chat_win);
  // keep message
  list_for_each(iter, &msg_list_head) {
    struct msg_list* m = container_of(iter, struct msg_list, list);
    struct user_t* u = get_user_or_req(m->msg.uid);
    if (u == NULL) {
      wprintw(chat_win, "\nuser_%d at %s:\n%s\n", m->msg.uid,
              fmt_time(m->msg.mtime), m->msg.msg);
    } else {
      wprintw(chat_win, "\n%s at %s:\n%s\n", u->name, fmt_time(m->msg.mtime),
              m->msg.msg);
    }
  }
  wrefresh(chat_win);
  wrefresh(input_win);
}

void init_screen() {
  setlocale(LC_ALL, "");
  main_win = initscr();
  if (main_win == NULL) {
    exit(-1);
  }

  noecho();
  cbreak();
  keypad(main_win, TRUE);
}

void init_window() {
  endwin();
  refresh();
  clear();

  int w = COLS;
  int chat_h = LINES * 0.8;
  int input_h = LINES * 0.2;

  chat_wbox = subwin(main_win, chat_h, w, 0, 0);
  chat_win = subwin(chat_wbox, chat_h - 2, w - 2, 1, 1);
  scrollok(chat_win, TRUE);
  box(chat_wbox, 0, 0);
  wrefresh(chat_wbox);
  wrefresh(chat_win);

  input_wbox = subwin(main_win, input_h, w, chat_h, 0);
  input_win = subwin(input_wbox, input_h - 2, w - 2, chat_h + 1, 1);
  box(input_wbox, 0, 0);
  wrefresh(input_wbox);
  wrefresh(input_win);

  refresh_chat_messages();
}

void sig_interupt() {
  // TODO
  exit(1);
}

char input_buf[128];
int input_len = 0;

void input_clear() {
  input_len = 0;
  input_buf[0] = '\0';
  wclear(input_win);
  wmove(input_win, 0, 0);
  wrefresh(input_win);
}

void input_delegate(chtype ch) {
  switch (ch) {
    case KEY_RESIZE:
      break;
    case KEY_BACKSPACE:
    case KEY_LEFT:
      if (input_len > 0) {
        input_buf[--input_len] = '\0';
        wprintw(input_win, "\b \b\0");
      } else {
        wprintw(input_win, "\b\0");
      }
      break;

    default:
      if (input_len < sizeof(input_buf)) {
        input_buf[input_len++] = ch;
        waddch(input_win, ch);
      } else {
        input_buf[input_len - 1] = ch;
        wprintw(input_win, "\b%c", ch);
      }
      break;
  }
  input_buf[input_len] = '\0';
  wrefresh(input_win);
}

void* udp_handler(void* _) {
  for (;;) {
    wait_udp_res();
    if (res_pkg->proto != CHAT_PACKAGE_PROTO) {
      debug_log("recv invalid pkg\n");
      continue;
    }
    struct chat_package* pkg = res_pkg;
    switch (pkg->type) {
      case Type_RES_USER: {
        struct user_t* user = (struct user_t*)malloc(sizeof(struct user_t));
        memcpy(user, res_data, sizeof(struct user_t));
        user_list[user->uid] = user;
      } break;

      case Type_RES_MSG: {
        struct msg_list* node = mk_res_msg_node();
        if (node == NULL) break;

        int msg_id = node->msg.id;
        struct list_head* pos = &msg_list_head;
        list_for_each_reverse(iter, &msg_list_head) {
          struct msg_list* m = container_of(iter, struct msg_list, list);
          if (m->msg.id < msg_id) {
            pos = iter->next;
            break;
          }
        }
        list_add_tail(&node->list, pos);
        refresh_chat_messages();
      } break;
      default:
        break;
    }
  }
  return NULL;
}

void* pull_handler(void* _) {
  int last_msg_id = 0;
  for (;;) {
    sleep(1);
    if (!list_empty(&msg_list_head)) {
      struct msg_list* last_msg_node =
          container_of(msg_list_head.prev, struct msg_list, list);
      last_msg_id = last_msg_node->msg.id;
    }
    ((struct req_get_msg*)req_buf)->msg_id = last_msg_id + 1;
    make_udp_req(Type_REQ_GET, sizeof(struct req_get_msg));
  }
  return NULL;
}

void send_msg(struct req_send_msg* msg) {
  int msg_off = offsetof(struct req_send_msg, msg);
  memcpy(req_buf, msg, msg_off);
  memcpy(req_buf + msg_off, msg->msg, msg->msg_len);
  make_udp_req(Type_REQ_SEND, msg_off + msg->msg_len);
}

void print_usage() {
  fprintf(stderr, "usage: chat_client -h ip_addr -p ip_port [nickname]\n");
}

int main(int argc, char* argv[]) {
  int opt = 0;
  opterr = 0;
  while ((opt = getopt(argc, argv, "p:h:")) != -1) {
    switch (opt) {
      case 'h':
        serv_ip = optarg;
        break;
      case 'p':
        serv_port = atoi(optarg);
        break;
      default:
        print_usage();
        exit(-1);
    }
  }
  argc -= optind;
  argv += optind;
  if (argc > 0) {
    strcpy(current_name, argv[0]);
  }

  signal(SIGINT, sig_interupt);
  signal(SIGWINCH, init_window);

  setup_socket(argc, argv);
  setup_connection();

  pthread_t udp_thread;
  pthread_t pull_thread;
  pthread_create(&udp_thread, NULL, udp_handler, NULL);
  pthread_create(&pull_thread, NULL, pull_handler, NULL);

  init_screen();
  init_window();
  input_clear();
  chtype ch;
  while ((ch = getch()) != 27) {
    switch (ch) {
      case 10:  // ENTER
        if (input_len > 0) {
          struct req_send_msg msg = {
              .uid = current_uid,
              .msg = input_buf,
              .msg_len = input_len,
          };
          send_msg(&msg);
          input_clear();
        }
        break;
      default:
        input_delegate(ch);
        break;
    }
  }

  return 0;
}
