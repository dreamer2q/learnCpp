#ifndef __CMD_H
#define __CMD_H

#include "common.h"

#define MAX_ARGV 32
#define MAX_FLAGS 10

enum flag {
  optional = 0,
  required,
};

// command flag definition
struct flag_t {
  const char short_opt;  // for -t
  const char* long_opt;  // for --t
  const char* desc;      // for -t foo
  const enum flag flag;  // required?
};

struct flag_arg {
  struct flag_t* f;
  const char* key;  // flag key
  const char* val;  // flag val, can be NULL
};

// command argument
struct cmd_arg {
  int argc;               // raw argc
  const char** argv;            // raw argv
  struct flag_arg* args;  // parsed argument flags
};

// builtin command definition
struct cmd_t {
  const char* cmd;  // 命令名称
  struct flag_t
      flags[MAX_FLAGS];  // 命令参数, 例如 bool: -t, string: -s abcdefg
  const int min_argc;    // 最少所需参数
  const char* usage;     // 使用说明
  int (*exec)(struct cmd_arg*);  // 执行函数
};

#define cmd_foreach(CMDS, C) for (C = CMDS; C && C->cmd; C++)

int cmd_parseline(char* buf, const char* argv[]);

int cmd_index_name(struct cmd_t* cmds, const char* cmd);

int cmd_exec(struct cmd_t* cmds, int argc, const char** argv);

#endif