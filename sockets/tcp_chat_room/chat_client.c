#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <getopt.h>
#include <locale.h>
#include "chat.h"

#define SERV_PORT 8081
short arg_serv_port = SERV_PORT;
const char* arg_serv_host = "127.0.0.1";
const char* arg_username;
name_t input_password;

int serv_fd;
pthread_t serv_thread;
pthread_mutex_t lock_w;
LIST_HEAD(chat_list_head);
struct list_head* iter;

struct {
  WINDOW* main;
  WINDOW* main_box;
  WINDOW* chat_list;
  WINDOW* chat_list_box;
  WINDOW* input;
  WINDOW* input_box;
  char input_buf[BUFSIZ];
  ssize_t input_len;
  pthread_mutex_t lock_w;
} nc;

void make_connection() {
  serv_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serv_fd < 0) {
    ERROR_EXIT("create socket error");
  }
  struct sockaddr_in servaddr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = inet_addr(arg_serv_host),
      .sin_port = htons(arg_serv_port),
  };

  if (connect(serv_fd, (struct sockaddr*)&servaddr, sizeof servaddr) < 0) {
    ERROR_EXIT("connect to server");
  }
  debug_log("connected %s:%d\n", arg_serv_host, arg_serv_port);
}

void sig_int() {
  close(serv_fd);
  endwin();
  exit(1);
}

void print_usage() {
  printf("%s: -h host -p port username\n", "chat_client");
  exit(0);
}

void parse_args(int argc, char* argv[]) {
  struct option opts[] = {
      {
          .name = "host",
          .has_arg = optional_argument,
          .flag = NULL,
          .val = 'h',
      },
      {
          .name = "port",
          .has_arg = optional_argument,
          .flag = NULL,
          .val = 'p',
      },
      {0},  // end mark
  };
  int ch;
  while ((ch = getopt_long(argc, argv, "h:p:", opts, NULL)) != -1) {
    switch (ch) {
      case 'p':
        arg_serv_port = atoi(optarg);
        break;
      case 'h':
        arg_serv_host = optarg;
        break;
      default:
        print_usage();
    }
  }
  argc -= optind;
  argv += optind;
  if (argc == 0) print_usage();
  arg_username = argv[0];
}

void ask_user_login() {
  debug_log("password for %s required\n", arg_username);
  printf("password: ");
  scanf("%s", input_password);
  struct login lg;
  strncpy(lg.username, arg_username, sizeof(name_t));
  strncpy(lg.password, input_password, sizeof(name_t));
  tpl_send(TYPE_LOGIN, serv_fd, "S(c#c#)", &lg, 32, 32);
}

#define wp(win, clr, fmt, args...)    \
  do {                                \
    pthread_mutex_lock(&nc.lock_w);   \
    wattron(win, COLOR_PAIR(clr));    \
    wprintw(win, fmt, ##args);        \
    wattroff(win, COLOR_PAIR(clr));   \
    wrefresh(win);                    \
    pthread_mutex_unlock(&nc.lock_w); \
  } while (0)

#define INPUT_COLOR 1
#define CHAT_NAME_COLOR 2
#define CHAT_TEXT_COLOR 3
#define CHAT_ME_COLOR 4

void init_ncurse() {
  setlocale(LC_ALL, "");
  nc.main = initscr();
  noecho();
  cbreak();
  keypad(nc.main, true);
  start_color();
  init_pair(INPUT_COLOR, COLOR_GREEN, COLOR_BLACK);
  init_pair(CHAT_NAME_COLOR, COLOR_CYAN, COLOR_BLACK);
  init_pair(CHAT_TEXT_COLOR, COLOR_GREEN, COLOR_BLACK);
  init_pair(CHAT_ME_COLOR, COLOR_RED, COLOR_GREEN);
  pthread_mutex_init(&nc.lock_w, NULL);
}

void init_screen() {
  endwin();
  refresh();
  clear();

  int w = COLS;
  int h_input = LINES * 0.2;
  if (h_input < 3) h_input = 3;
  int h_chat = LINES - h_input;

  nc.chat_list_box = subwin(nc.main, h_chat, w, 0, 0);
  nc.chat_list = subwin(nc.chat_list_box, h_chat - 2, w - 2, 1, 1);

  nc.input_box = subwin(nc.main, h_input, w, h_chat, 0);
  nc.input = subwin(nc.input_box, h_input - 2, w - 2, h_chat + 1, 1);

  scrollok(nc.chat_list, true);
  scrollok(nc.input, true);

  box(nc.chat_list_box, 0, 0);
  box(nc.input_box, 0, 0);

  wrefresh(nc.main);
  wrefresh(nc.chat_list_box);
  wrefresh(nc.chat_list);
  wrefresh(nc.input_box);
  wrefresh(nc.input);
}

void wrefresh_chat_list(WINDOW* chat) {
  wclear(chat);
  list_for_each(iter, &chat_list_head) {
    struct chat_node* node = container_of(iter, struct chat_node, list);
    const char* uname = node->chat.username;
    const char* text = node->chat.text;

    bool is_me = strncmp(uname, arg_username, sizeof(name_t)) == 0;
    if (is_me) {
      wp(chat, CHAT_ME_COLOR, "\n%s\n", uname);
      wp(chat, CHAT_TEXT_COLOR, "%s\n", text);
    } else {
      wp(chat, CHAT_NAME_COLOR, "\n%s\n", uname);
      wp(chat, CHAT_TEXT_COLOR, "%s\n", text);
    }
  }
}

void wrefresh_user_input(WINDOW* input) {
  wclear(input);
  wp(input, INPUT_COLOR, nc.input_buf);
}

void clear_user_input() {
  nc.input_len = 0;
  nc.input_buf[0] = '\0';
}

void resize_handler() {
  init_screen();
  wrefresh_chat_list(nc.chat_list);
  wrefresh_user_input(nc.input);
}

void* recv_handler(void* _) {
  for (;;) {
    struct pkg_t pkg = {0};
    if (!recv_pkg(serv_fd, &pkg)) {
      debug_log("pkg error\n");
      break;
    }

    switch (pkg.type) {
      case TYPE_LOGIN_RESPONSE: {
        struct login_response lg_res;
        tpl_recv(serv_fd, "S(c)", &lg_res);
        debug_log("login result: %d\n", lg_res.result);
      } break;

      case TYPE_WELCOME: {
        char* msg_ptr;
        struct show_chat chat_item;
        tpl_node* tn = tpl_map("sA(S(c#s))", &msg_ptr, &chat_item, 32);
        tpl_load(tn, TPL_FD, serv_fd);
        tpl_unpack(tn, 0);
        int item_len = tpl_Alen(tn, 1);
        for (int i = 0; i < item_len; i++) {
          tpl_unpack(tn, 1);
          struct chat_node* chat_node =
              (struct chat_node*)malloc(sizeof(struct chat_node));
          chat_node->chat = chat_item;
          list_add_tail(&chat_node->list, &chat_list_head);
          printf("\n%s:\n> %s\n", chat_item.username, chat_item.text);
        }
        tpl_free(tn);
        // debug_log("%s\n", msg_ptr);
        free(msg_ptr);
      } break;

      case TYPE_SHOW_CHAT: {
        struct show_chat show = {0};
        tpl_recv(serv_fd, "S(c#s)", &show, 32);
        struct chat_node* chat_node =
            (struct chat_node*)malloc(sizeof(struct chat_node));
        chat_node->chat = show;
        list_add_tail(&chat_node->list, &chat_list_head);
        // printf("\n%s:\n> %s\n", show.username, show.text);
      } break;
    }
    wrefresh_chat_list(nc.chat_list);
  }
  close(serv_fd);
  return NULL;
}

int main(int argc, char* argv[]) {
  parse_args(argc, argv);
  make_connection();
  ask_user_login();

  init_ncurse();
  init_screen();

  signal(SIGINT, sig_int);
  signal(SIGWINCH, resize_handler);

  pthread_mutex_init(&lock_w, NULL);
  pthread_create(&serv_thread, NULL, recv_handler, NULL);

  for (;;) {
    chtype ch = getch();
    switch (ch) {
      case KEY_RESIZE:
        break;
      case KEY_BACKSPACE:
      case KEY_LEFT:
        if (nc.input_len > 0) {
          nc.input_buf[--nc.input_len] = '\0';
        }
        break;

      case 10:
      case KEY_ENTER: {
        struct chat cc = {.text = nc.input_buf};
        tpl_send(TYPE_CHAT, serv_fd, "S(s)", &cc);
        clear_user_input();
      } break;

      default:
        if (nc.input_len < sizeof(nc.input_buf)) {
          nc.input_buf[nc.input_len++] = ch;
        } else {
          nc.input_buf[nc.input_len - 1] = ch;
        }
        break;
    }
    nc.input_buf[nc.input_len] = '\0';
    wrefresh_user_input(nc.input);
  }
  return 0;
}
