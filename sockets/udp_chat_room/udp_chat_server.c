#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "chat.h"

const int SERV_PORT = 3001;

void exit_handler() { printf("echo server terminated\n"); }

// chat server
int sockfd;
char recvbuf[1 << 16];  // UDP receive buffer
char resbuf[1 << 16];   // UDP response buffer
char* resbody = resbuf + sizeof(struct chat_package);
struct sockaddr_in clnt_addr;
socklen_t clnt_len = sizeof clnt_addr;
ssize_t recv_len;

LIST_HEAD(msg_list_head);
struct list_head* iter;

uint32_t next_msg_id = 1;

void setup_socket() {
  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd < 0) {
    fprintf(stderr, "error creating socket\n");
    exit(-1);
  }

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERV_PORT);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof serv_addr) < 0) {
    fprintf(stderr, "error binding to port: %d\n", SERV_PORT);
    exit(-1);
  }
}

void sendres(uint8_t type, uint16_t sz) {
  struct chat_package pkg = {
      .proto = CHAT_PACKAGE_PROTO,
      .type = type,
      .size = sz,
      .checksum = 0,
  };
  memcpy(resbuf, &pkg, sizeof pkg);
  ssize_t sent_len = sendto(sockfd, resbuf, sz + CHAT_PACKAGE_SIZE, 0,
                            (struct sockaddr*)&clnt_addr, sizeof clnt_addr);
  if (sent_len != sz + CHAT_PACKAGE_SIZE) {
    fprintf(stderr, "send reply error\n");
  }
}

void send_res_ok() { sendres(Type_RES_OK, 0); }

void send_res_empty() { sendres(Type_RES_EMPTY, 0); }

void send_msg_res(struct msg_t* msg) {
  int offset = offsetof(struct msg_t, msg);
  memcpy(resbody, msg, offset);
  memcpy(resbody + offset, msg->msg, msg->msg_len);
  sendres(Type_RES_MSG, offset + msg->msg_len);
}

void send_user_res(struct user_t* user) {
  memcpy(resbody, user, sizeof(struct user_t));
  sendres(Type_RES_USER, sizeof(struct user_t));
}

void handler() {
  struct chat_package* pkg = (struct chat_package*)recvbuf;
  if (pkg->proto != CHAT_PACKAGE_PROTO) {
    fprintf(stderr, "recv invalid chat package\n");
    return;
  }

  const char* data = recvbuf + sizeof(struct chat_package);
  switch (pkg->type) {
    case Type_REQ_JOIN: {
      struct req_join_user* joiner = (struct req_join_user*)data;
      struct user_t* user = (struct user_t*)malloc(sizeof(struct user_t));
      user->uid = get_next_free_uid();
      user->join_time = time(NULL);
      strcpy(user->name, joiner->name);
      user_list[user->uid] = user;

      struct res_join_user res = {
          .flag = 1,
          .uid = user->uid,
          .join_time = user->join_time,
          .last_msg_id = next_msg_id - 1,
      };
      memcpy(resbody, &res, sizeof res);
      sendres(Type_RES_JOIN, sizeof res);

      debug_log("new user join from(%s:%d): %d: %s\n",
                inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port),
                user->uid, user->name);
    } break;

    case Type_REQ_SEND: {
      struct req_send_msg msg;
      memcpy(&msg, data, sizeof(struct req_send_msg));
      msg.msg = data + offsetof(struct req_send_msg, msg);

      if (!is_valid_uid(msg.uid)) {
        debug_log("user_%d not found\n", msg.uid);
        break;
      }

      uint16_t body_len = msg.msg_len;
      char* body_buf = (char*)malloc(body_len + 1);
      memcpy(body_buf, msg.msg, body_len);
      body_buf[body_len] = '\0';

      struct msg_t new_msg = {
          .id = next_msg_id++,
          .uid = msg.uid,
          .mtime = time(NULL),
          .mtype = 1,  // TODO 消息类型
          .msg_len = body_len,
          .msg = body_buf,
      };

      struct msg_list* msg_node = malloc(sizeof(struct msg_list));
      msg_node->msg = new_msg;
      list_add_tail(&msg_node->list, &msg_list_head);

      send_res_ok();
      debug_log("new_msg: user_%d: msg_%d: %s\n", new_msg.uid, new_msg.id,
                new_msg.msg);
    } break;

    case Type_REQ_GET: {
      struct req_get_msg* msg_get = (struct req_get_msg*)data;
      uint32_t msg_id = msg_get->msg_id;
      if (msg_id >= next_msg_id) {
        // debug_log("req last_msg_%d: off the last one\n", last_msg_id);
        break;
      }

      struct msg_t* msg = NULL;
      list_for_each_reverse(iter, &msg_list_head) {
        struct msg_list* msg_node = container_of(iter, struct msg_list, list);
        if (msg_node->msg.id == msg_id) {
          msg = &msg_node->msg;
          break;
        }
      }
      if (msg == NULL) {
        debug_log("req last_msg_%d: msg not found\n", msg_id);
        break;
      }

      send_msg_res(msg);
      debug_log("req last_msg_%d: (%s) user_%d: %s\n", msg_id,
                fmt_time(msg->mtime), msg->uid, msg->msg);
    } break;

    case Type_REQ_USER: {
      struct req_get_user* user_get = (struct req_get_user*)data;
      uint32_t get_uid = user_get->uid;
      if (!is_valid_uid(get_uid)) {
        send_res_empty();
        break;
      }

      struct user_t* user = user_list[get_uid];
      send_user_res(user);
      debug_log("%s: get userinfo: %d: %s\n", inet_ntoa(clnt_addr.sin_addr),
                user->uid, user->name);
    } break;

    default:
      break;
  }
}

int main() {
  atexit(exit_handler);
  setup_socket();
  printf("listening at :%d\n", SERV_PORT);
  printf("chat server started\n");
  printf("waiting for incoming client\n");

  for (;;) {
    recv_len = recvfrom(sockfd, recvbuf, sizeof recvbuf, 0,
                        (struct sockaddr*)&clnt_addr, &clnt_len);
    if (recv_len > 0) {
      handler();
    }
  }

  return 0;
}