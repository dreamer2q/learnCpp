#ifndef __CHAT_H
#define __CHAT_H

#include <stdint.h>
#include <time.h>
#include "include/list.h"

typedef signed char BOOL;
// #define TRUE ((BOOL)1)
// #define FALSE (!TRUE)

const char* fmt_time(time_t t) {
  static char fmt_buf[128] = {0};
  strftime(fmt_buf, sizeof fmt_buf, "%F_%T", localtime(&t));
  return fmt_buf;
}

const char* now_time() { return fmt_time(time(NULL)); }

#define debug_log(log, args...) fprintf(stderr, "%s: " log, now_time(), ##args)

const uint16_t CHAT_PACKAGE_PROTO = 0xF0F1;

typedef char uname_t[32];

#define Type_REQ_JOIN 1
#define Type_REQ_SEND 2
#define Type_REQ_GET 3
#define Type_REQ_USER 4
#define Type_RES_JOIN 101
#define Type_RES_MSG 102
#define Type_RES_USER 104
#define Type_RES_OK 105
#define Type_RES_EMPTY 106
#define MAX_USER_SIZE 100

struct chat_package {
  uint16_t proto;    // 协议头
  uint16_t size;     // 包大小
  uint8_t type;      // 数据类型
  uint8_t checksum;  // 头校验和
};

const int CHAT_PACKAGE_SIZE = sizeof(struct chat_package);

// type 1
struct req_join_user {
  uname_t name;
};

// type 101
struct res_join_user {
  uint8_t flag;          // 0x01 表示OK
  uint32_t last_msg_id;  // 最新一条消息的 ID
  uint16_t uid;          // 分配的 ID
  time_t join_time;      // 进入时间
};

// type 2
struct req_send_msg {
  uint16_t uid;      // 发送用户
  uint16_t msg_len;  // 消息长度
  const char* msg;   // 消息内容
};

// type 3
struct req_get_msg {
  uint32_t msg_id;  // 获取 msg_id 对应的消息
};

struct req_get_user {
  uint16_t uid;  // 用户 ID
};

struct user_t {
  uint16_t uid;      // 用户 ID
  time_t join_time;  // 加入时间
  uname_t name;      // 用户昵称
};

// type 102
struct msg_t {
  uint32_t id;       // 消息 ID, 从 1 开始
  uint8_t mtype;     // 消息类型
  time_t mtime;      // 消息时间
  uint16_t uid;      // 用户 ID
  uint16_t msg_len;  // 消息长度
  const char* msg;   // 消息内容
};

struct msg_list {
  struct msg_t msg;
  struct list_head list;
};

struct user_t* user_list[MAX_USER_SIZE];

uint16_t get_next_free_uid() {
  for (uint16_t i = 1; i < MAX_USER_SIZE; i++) {
    if (user_list[i] == NULL) {
      return i;
    }
  }
  return 0;
}

BOOL is_valid_uid(uint16_t uid) {
  return uid > 0 && uid < MAX_USER_SIZE && user_list[uid] != NULL;
}

#endif
