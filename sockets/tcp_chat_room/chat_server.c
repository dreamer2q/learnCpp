#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "chat.h"

#define SERV_ADDR INADDR_ANY
#define SERV_PORT 8081

int sockfd = 0;

void setup_socket() {
  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd < 0) {
    ERROR_EXIT("create socket error");
  }

  struct sockaddr_in servaddr = {
      .sin_family = AF_INET,
      .sin_port = htons(SERV_PORT),
      .sin_addr.s_addr = SERV_ADDR,
  };
  if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof servaddr) == -1) {
    ERROR_EXIT("socket binding error");
  }

  if (listen(sockfd, 10) == -1) {
    ERROR_EXIT("socket listening error");
  }
}

void signal_interupt() {
  close(sockfd);
  debug_log("terminated\n");
  exit(0);
}

LIST_HEAD(clnt_list_head);
LIST_HEAD(chat_list_head);
struct list_head* iter;
size_t chat_list_count = 0;

struct clnt_node {
  pthread_t thread;
  int clnt_fd;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_len;
  struct list_head list;
  struct login lg;
};

void* clnt_handler(void* args) {
  struct clnt_node* clnt = (struct clnt_node*)args;
  int fd = clnt->clnt_fd;
  debug_log("accept client: %s:%d\n", inet_ntoa(clnt->clnt_addr.sin_addr),
            ntohs(clnt->clnt_addr.sin_port));
  for (;;) {
    struct pkg_t pkg;
    if (!recv_pkg(fd, &pkg)) {
      debug_log("pkg error\n");
      break;
    }

    // tpl_node* tn;
    switch (pkg.type) {
      case TYPE_LOGIN: {
        struct login lg = {0};
        tpl_recv(fd, "S(c#c#)", &lg, 32, 32);
        debug_log("user_login: %s:%s\n", lg.username, lg.password);

        // Login Check
        struct clnt_node* found = NULL;
        list_for_each(iter, &clnt_list_head) {
          struct clnt_node* node = container_of(iter, struct clnt_node, list);
          if (strncmp(node->lg.username, lg.username, sizeof(name_t)) == 0) {
            found = node;
            break;
          }
        }

        struct login_response lg_res = {.result = 1};
        if (found) {
          if (strncmp(found->lg.password, lg.password, sizeof(name_t)) == 0) {
            lg_res.result = 2;
            tpl_send(TYPE_LOGIN_RESPONSE, fd, "S(c)", &lg_res);
            debug_log("restore login\n");
          } else {
            // wrong password
            lg_res.result = 0;
            tpl_send(TYPE_LOGIN_RESPONSE, fd, "S(c)", &lg_res);
            debug_log("wrong password\n");
            goto shutdown;
          }
        }

        // add list node
        clnt->lg = lg;
        list_add_tail(&clnt->list, &clnt_list_head);
        tpl_send(TYPE_LOGIN_RESPONSE, fd, "S(c)", &lg_res);
        debug_log("send result: %d\n", lg_res.result);

        char msg_buf[BUFSIZ] = {0};
        sprintf(msg_buf, "welcome to tcp-chat room, you have logged as %s",
                lg.username);
        uint8_t msg_cnt = chat_list_count > 10 ? 10 : chat_list_count;
        struct show_chat chat_item;
        char* msg_ptr = msg_buf;
        tpl_node* tn = tpl_map("sA(S(c#s))", &msg_ptr, &chat_item, 32);
        tpl_pack(tn, 0);
        list_for_each(iter, &chat_list_head) {
          struct chat_node* n = container_of(iter, struct chat_node, list);
          chat_item = n->chat;
          tpl_pack(tn, 1);
          debug_log("tpl_pack: %d: %s\n", msg_cnt, chat_item.text);
          if (--msg_cnt == 0) break;
        }
        write_pkg(fd, TYPE_WELCOME);
        tpl_dump(tn, TPL_FD, fd);
        tpl_free(tn);
        debug_log("welcome: %s\n", msg_buf);
      } break;

      case TYPE_CHAT: {
        struct chat chat;
        tpl_recv(fd, "S(s)", &chat);
        debug_log("chat: %s\n", chat.text);
        struct show_chat show = {.text = chat.text};
        strcpy(show.username, clnt->lg.username);

        struct chat_node* node =
            (struct chat_node*)malloc(sizeof(struct chat_node));
        node->chat = show;
        list_add_tail(&node->list, &chat_list_head);
        chat_list_count++;

        tpl_node* tn = tpl_map("S(c#s)", &show, 32);
        tpl_pack(tn, 0);
        // TODO 广播消息
        list_for_each_reverse(iter, &clnt_list_head) {
          struct clnt_node* cnt = container_of(iter, struct clnt_node, list);
          int cnt_fd = cnt->clnt_fd;
          write_pkg(cnt_fd, TYPE_SHOW_CHAT);
          tpl_dump(tn, TPL_FD, cnt_fd);
        }
        tpl_free(tn);
        tn = NULL;
      } break;
    }
  }

shutdown:
  debug_log("shutdown: %d\n", clnt->clnt_fd);
  if (!list_empty(&clnt->list)) {
    list_del(&clnt->list);
  }
  close(clnt->clnt_fd);
  return NULL;
}

int main(int argc, char* argv[]) {
  printf(CHAT_VERSION "\n");
  setup_socket();
  printf("server listening at :%d\n", SERV_PORT);

  signal(SIGINT, signal_interupt);

  for (;;) {
    struct sockaddr_in clnt_addr;
    socklen_t clnt_len;
    int clnt_fd;

    clnt_fd = accept(sockfd, (struct sockaddr*)&clnt_addr, &clnt_len);
    if (clnt_fd == -1) {
      perror("accept client socket");
      continue;
    }

    struct clnt_node clnt = {
        .clnt_addr = clnt_addr,
        .clnt_fd = clnt_fd,
        .clnt_len = clnt_len,
        .list = {0},
    };
    struct clnt_node* clnt_node = (struct clnt_node*)malloc(sizeof clnt);
    memcpy(clnt_node, &clnt, sizeof clnt);
    pthread_create(&clnt_node->thread, NULL, clnt_handler, clnt_node);
  }

  close(sockfd);
  return 0;
}
