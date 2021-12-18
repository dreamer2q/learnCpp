#include "common.h"
#include "cmd.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int cmd_parseline(char* buf, const char* argv[]) {
  buf[strlen(buf) - 1] = ' ';
  while (*buf && (*buf == ' ')) {
    buf++;
  }

  char* delim;
  int argc = 0;
  while ((delim = strchr(buf, ' '))) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;

    while (*buf && (*buf == ' ')) {
      buf++;
    }
  }
  argv[argc] = NULL;
  return argc;
}

int flag_index(struct flag_arg* flags, const char* key) {
  int i = 0;
  for (struct flag_arg* flag = flags; flag->key; flag++) {
    if (compare(key, ==, flag->key)) {
      return i;
    }
    i++;
  }
  return -1;
}

int cmd_index_name(struct cmd_t* cmds, const char* cmd) {
  int index = 0;
  struct cmd_t* c;
  cmd_foreach(cmds, c) {
    if (compare(cmd, ==, c->cmd)) {
      return index;
    }
    index++;
  }
  return -1;
}

int cmd_parse_flags(struct flag_t* defs, const char** argv,
                    struct flag_arg* res) {
  int i = 0;
  for (const char** arg = argv; *arg != NULL; arg++) {
    const char* a = *arg;
    if (a[0] != '-') continue;
    int indef = -1;
    bool islong = a[1] == '-';
    for (struct flag_t* flag = defs; flag->desc; flag++) {
      struct flag_arg fa = {.f = flag};
      if (islong) {
        if (compare(a + 2, ==, flag->long_opt)) {
          fa.key = flag->long_opt;
        }
      } else {
        if (strlen(a) == 2 && a[1] == flag->short_opt) {
          fa.key = flag->long_opt;
        }
      }
      if (fa.key) {
        if (arg[1] && arg[1][0] != '-') {
          fa.val = arg[1];
          arg++;
        }
        res[i++] = fa;
        break;
      }
    }
  }
  return i;
}

int flag_cmp(const void* f1, const void* f2) {
  const struct flag_arg* a1 = (struct flag_arg*)f1;
  const struct flag_arg* a2 = (struct flag_arg*)f2;
  return strcmp(a1->key, a2->key);
}

void cmd_print_usage(struct cmd_t* execcmd) {
  printf("Usage of %s: %s\n\n", execcmd->cmd, execcmd->usage);
  for (struct flag_t* f = execcmd->flags; f->desc; f++) {
    printf("\t -%c, --%s \t\t\t %s\n", f->short_opt, f->long_opt, f->desc);
  }
}

int cmd_exec(struct cmd_t* execcmd, int argc, const char** argv) {
  if (execcmd == NULL || argc == 0 || argv == NULL) return -1;

  if (execcmd->min_argc > argc - 1) {
    cmd_print_usage(execcmd);
    return -1;
  }

  struct flag_arg fargs[MAX_FLAGS] = {NULL};
  int flen = cmd_parse_flags(execcmd->flags, argv, fargs);
  qsort(fargs, flen, sizeof(struct flag_arg), flag_cmp);

  // find duplicated flag
  for (int i = 0; i < flen - 1; i++) {
    if (compare(fargs[i].key, ==, fargs[i + 1].key)) {
      printf("cmd_exec: duplicated flag %s\n", fargs->key);
      return -1;
    }
  }

  // required
  for (struct flag_t* flag = execcmd->flags; flag->desc; flag++) {
    struct flag_arg fa = {.f = flag};
    if (flag->flag == required) {
      int has = false;
      if (flag_index(fargs, flag->long_opt) == -1) {
        printf("cmd_exec: missing required flag: %s\n", flag->long_opt);
        return -1;
      }
    }
  }

  struct cmd_arg cmdarg = {
      .argc = argc,
      .argv = argv,
      .args = fargs,
  };
  if (execcmd->exec) {
    execcmd->exec(&cmdarg);
  }
  return 0;
}
