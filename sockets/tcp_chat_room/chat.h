#ifndef __CHAT_H__
#define __CHAT_H__

#include <time.h>
#include <errno.h>
#include "include/list.h"
#include "tpl.h"

#define ERROR_EXIT(msg)                                       \
  do {                                                        \
    fprintf(stderr, msg ": %d %s\n", errno, strerror(errno)); \
    exit(errno);                                              \
  } while (0)

#define CHAT_VERSION "tcp-chat v0.1 by Dreamer2q"

typedef signed char BOOL;

const char* time_fmt(time_t t) {
  static char fmt_buf[128] = {0};
  strftime(fmt_buf, sizeof fmt_buf, "%F_%T", localtime(&t));
  return fmt_buf;
}

const char* time_now() { return time_fmt(time(NULL)); }

#define debug_log(log, args...) fprintf(stderr, "%s: " log, time_now(), ##args)

typedef char name_t[32];

#define PKG_PROTO 0x1F2F
#define TYPE_LOGIN 1
#define TYPE_LOGIN_RESPONSE 101
#define TYPE_CHAT 2
#define TYPE_SHOW_CHAT 3
#define TYPE_WELCOME 4

struct pkg_t {
  uint16_t proto;
  uint8_t type;
};

struct login {
  name_t username;
  name_t password;
};

struct login_response {
  uint8_t result;
};

struct chat {
  char* text;
};

struct show_chat {
  name_t username;
  char* text;
};

struct chat_node {
  struct show_chat chat;
  struct list_head list;
};

struct welcome_t {
  char* message;
  uint8_t count;
  struct show_chat* chats;
};

BOOL recv_pkg(int fd, struct pkg_t* pkg) {
  tpl_node* tn = tpl_map("S(vc)", pkg);
  if (tpl_load(tn, TPL_FD, fd) < 0) {
    return 0;
  }
  tpl_unpack(tn, 0);
  if (pkg->proto != PKG_PROTO) {
    return 0;
  }
  tpl_free(tn);
  return 1;
}

BOOL write_pkg(int fd, uint8_t pkg_type) {
  struct pkg_t pkg = {
      .proto = PKG_PROTO,
      .type = pkg_type,
  };
  return tpl_jot(TPL_FD, fd, "S(vc)", &pkg) > 0;
}

#define tpl_recv(fd, fmt, args...)              \
  do {                                          \
    tpl_node* __tn_node = tpl_map(fmt, ##args); \
    tpl_load(__tn_node, TPL_FD, fd);            \
    tpl_unpack(__tn_node, 0);                   \
    tpl_free(__tn_node);                        \
  } while (0)

#define tpl_send(type, fd, fmt, args...) \
  do {                                   \
    write_pkg(fd, type);                 \
    tpl_jot(TPL_FD, fd, fmt, ##args);    \
  } while (0)

#endif
