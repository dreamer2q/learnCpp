#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include "common.h"
#include "filesys.h"
#include "cmd.h"

int builtin_ver(struct cmd_arg* args);
int builtin_ls(struct cmd_arg* args);
int builtin_cd(struct cmd_arg* args);
int builtin_pwd(struct cmd_arg* args);
int builtin_disk(struct cmd_arg* args);
int builtin_xcd(struct cmd_arg* args);
int builtin_rmdir(struct cmd_arg* args);
int builtin_mkdir(struct cmd_arg* args);
int builtin_edit(struct cmd_arg* args);
int builtin_rm(struct cmd_arg* args);
int builtin_touch(struct cmd_arg* args);
int builtin_cat(struct cmd_arg* args);
int builtin_help(struct cmd_arg* args);
int builtin_exit(struct cmd_arg* args);
int builtin_import(struct cmd_arg* args);
int builtin_export(struct cmd_arg* args);

int builtin_test(struct cmd_arg* args) {
  const char* testfile = "test.c";
  const char testbuf[] = "this is a test line\n";
  int fd = fat_open(testfile);
  if (fd != -1) {
    fat_trunc(fd, sizeof(testbuf));
    fat_write(fd, testbuf, sizeof(testbuf));
    fat_close(fd);
  }
}

struct cmd_t builtin_commands[] = {
    {
        .cmd = "test",
        .exec = builtin_test,
        .min_argc = 0,
        .usage = "debug test",
    },
    {
        .cmd = "ver",
        .exec = builtin_ver,
        .min_argc = 0,
        .flags =
            {
                {
                    .short_opt = 'v',
                    .long_opt = "verbose",
                    .desc = "show more information",
                    .flag = required,
                },
            },
        .usage = "display version information",
    },
    {
        .cmd = "help",
        .exec = builtin_help,
        .min_argc = 0,
        .flags = {},
        .usage = "show builtin commands helps",
    },
    {
        .cmd = "exit",
        .exec = builtin_exit,
        .min_argc = 0,
        .flags = {},
        .usage = "exit file system",
    },
    {
        .cmd = "disk",
        .exec = builtin_disk,
        .min_argc = 1,
        .flags = {},
        .usage = "builtin disk management",
    },
    {
        .cmd = "cd",
        .exec = builtin_cd,
        .min_argc = 1,
        .flags = {},
        .usage = "change current working directory",
    },
    {
        .cmd = "pwd",
        .exec = builtin_pwd,
        .min_argc = 0,
        .flags = {},
        .usage = "display current working directory",
    },
    {
        .cmd = "ls",
        .exec = builtin_ls,
        .min_argc = 0,
        .flags = {},
        .usage = "display current directories/files",
    },
    {
        .cmd = "cat",
        .exec = builtin_cat,
        .min_argc = 1,
        .flags =
            {
                {
                    .desc = "show line number",
                    .flag = optional,
                    .long_opt = "lineno",
                    .short_opt = 'n',
                },
            },
        .usage = "display the file content",
    },
    {
        .cmd = "edit",
        .exec = builtin_edit,
        .min_argc = 1,
        .flags = {},
        .usage = "edit the file content",
    },
    {
        .cmd = "touch",
        .exec = builtin_touch,
        .min_argc = 1,
        .flags = {},
        .usage = "create an empty file",
    },
    {
        .cmd = "rm",
        .exec = builtin_rm,
        .min_argc = 1,
        .flags = {},
        .usage = "remove a file",
    },
    {
        .cmd = "mkdir",
        .exec = builtin_mkdir,
        .min_argc = 1,
        .flags = {},
        .usage = "make a directory",
    },
    {
        .cmd = "rmdir",
        .exec = builtin_rmdir,
        .min_argc = 1,
        .flags = {},
        .usage = "remove a directory",
    },
    {
        .cmd = "!cd",
        .exec = builtin_xcd,
        .min_argc = 1,
        .flags = {},
        .usage = "change external working directory",
    },
    {
        .cmd = "import",
        .exec = builtin_import,
        .min_argc = 1,
        .flags = {},
        .usage = "import a file into filesystem",
    },
    {
        .cmd = "export",
        .exec = builtin_export,
        .min_argc = 1,
        .flags = {},
        .usage = "export a file to external filesystem",
    },

    {
        // mark for the end
    },
};

struct cmd_t* isbuiltin_command(const char* cmd) {
  int i = cmd_index_name(builtin_commands, cmd);
  if (i != -1) {
    return builtin_commands + i;
  }
  return NULL;
}

void eval(const char* cmd) {
  char buf[BUFSIZ];
  const char* argv[MAX_ARGV];
  strcpy(buf, cmd);
  int argc = cmd_parseline(buf, argv);
  if (argc == 0) return;

  struct cmd_t* builtin = isbuiltin_command(argv[0]);

  if (!builtin) {
    if (argv[0][0] != '!') {
      printf("%s: builtin command not found.\n", argv[0]);
      return;
    }
    // exec external cmd
    pid_t pid;
    int status;
    if ((pid = fork()) == 0) {
      // child process
      if (execvp(argv[0] + 1, argv) < 0) {
        printf("%s: command not found.\n", argv[0]);
        exit(-1);
      }
    } else {
      if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid error");
      }
      printf("\n");
    }
    return;
  }

  // handle builtin cmds
  int ret = cmd_exec(builtin, argc, argv);
  return;
}

void print_usage(const char* cmd, const char* opt) {
  // Usage: touch filename
  printf("Usage: %s %s\n", cmd, opt);
}

int builtin_ls(struct cmd_arg* args) {
  int len;
  char cwd[128];
  struct fcb_t* list = fat_list(&len);
  fat_getcwd(cwd, sizeof(cwd));
  printf("Directory of %s \nTotal: %d\n\n", cwd, len);
  for (int i = 0; i < len; i++) {
    if (list[i].use_state) {
      char datetime[BUFSIZ] = {0};
      sprintf(datetime, "%04d-%02d-%02d %02d:%02d", fat_get_year(list[i].date),
              fat_get_month(list[i].date), fat_get_day(list[i].date),
              fat_get_hour(list[i].time), fat_get_minute(list[i].time),
              fat_get_second(list[i].time));
      if (list[i].attr & FAT_ATTR_DIR) {
        printf("%s\t<DIR>\t%s\n", datetime, list[i].filename);
      } else {
        printf("%s\t%-5d\t%s\n", datetime, list[i].length, list[i].filename);
      }
    }
  }
  return 0;
}

int builtin_cd(struct cmd_arg* args) {
  if (args->argc < 2) {
    print_usage("cd", "dirname");
  } else {
    fat_chdir(args->argv[1]);
  }
  return 0;
}

int builtin_pwd(struct cmd_arg* args) {
  char cwd[128];
  fat_getcwd(cwd, sizeof cwd);
  printf("%s\n\n", cwd);
  return 0;
}

int builtin_disk(struct cmd_arg* args) { return 0; }

int builtin_xcd(struct cmd_arg* args) {
  if (args->argc < 2) {
    print_usage("!cd", "target_dir");
  } else {
    if (chdir(args->argv[1]) < 0) {
      perror("!cd");
    }
  }
  return 0;
}

int builtin_mkdir(struct cmd_arg* args) {
  if (args->argc < 2) {
    print_usage("mkdir", "filename");
  } else {
    fat_mkdir(args->argv[1]);
  }
  return 0;
}

int builtin_rmdir(struct cmd_arg* args) {
  if (args->argc < 2) {
    print_usage("rmdir", "filename");
  } else {
    fat_rmdir(args->argv[1]);
  }
  return 0;
}

int builtin_rm(struct cmd_arg* args) {
  if (args->argc < 2) {
    print_usage("rm", "filename");
  } else {
    fat_delete(args->argv[1]);
  }
  return 0;
}

int builtin_touch(struct cmd_arg* args) {
  if (args->argc < 2) {
    print_usage("touch", "filename");
  } else {
    fat_create(args->argv[1]);
  }
  return 0;
}

int builtin_cat(struct cmd_arg* args) {
  char* buf;
  size_t cap, line = 0;
  bool hasno = flag_index(args->args, "lineno") != -1;
  int fd = fat_open(args->argv[1]);
  if (fd != -1) {
    int len;
    while ((len = fat_getline(&buf, &cap, fd)) > 0) {
      if (hasno) {
        printf(GREEN("%4d") "  %s", ++line, buf);
      } else {
        printf("%s", buf);
      }
    }
    printf("\n");
    fat_close(fd);
  }
  return 0;
}

int builtin_edit(struct cmd_arg* args) {
  void openEditor(const char* filename);

  pid_t pid;
  const char* filename = args->argc == 2 ? args->argv[1] : NULL;
  if ((pid = fork()) != -1) {
    if (pid == 0) {  // child
      openEditor(filename);
    } else {  // parent
      int status;
      assert(waitpid(pid, &status, 0) >= 0, "waitpid");
      printf("editor exited: %d\n", status);
    }
  }
}

int builtin_help(struct cmd_arg* args) {
  printf("Builtin Commands: \n\n");
  struct cmd_t* cmd;
  cmd_foreach(builtin_commands, cmd) {
    printf("  %s\n\t%s\n", cmd->cmd, cmd->usage);
  }
  printf("\n");
  return 0;
}

int builtin_exit(struct cmd_arg* args) {
  exitsys();
  printf("goodbye~\n");
  exit(0);
  return 0;
}

int builtin_import(struct cmd_arg* args) {
  const char* target = args->argv[1];
  const char* source = args->argc < 3 ? target : args->argv[2];
  if (fat_create(target) < 0) {
    printf("target file already exists");
    return -1;
  }
  int fd0 = fat_open(target);
  if (fd0 < 0) {
    printf("open target file error");
    return -1;
  }
  int fd1 = open(source, O_RDONLY);
  if (fd1 < 0) {
    perror("open target file");
    return -1;
  }
  char buf[BLOCK_SIZE];
  int len = 0;
  while ((len = read(fd1, buf, sizeof buf)) > 0) {
    if (fat_write(fd0, buf, len) < 0) {
      printf("write target error");
      break;
    }
  }
  fat_close(fd0);
  close(fd1);
}

int builtin_export(struct cmd_arg* args) {
  if (args->argc < 2) {
    print_usage("export", "source target");
  } else {
    const char** argv = args->argv;
    const char* target_name = args->argc == 3 ? argv[2] : argv[1];
    // 文件导出
    int fd0 = fat_open(argv[1]);
    if (fd0 < 0) {
      printf("open source file error");
      return -1;
    }
    int fd1 = open(target_name, O_CREAT | O_TRUNC | O_WRONLY);
    if (fd1 < 0) {
      perror("open target file");
      return -1;
    }
    char buf[BUFSIZ];
    int len = 0;
    while ((len = fat_read(fd0, buf, BUFSIZ)) > 0) {
      if (write(fd1, buf, len) < 0) {
        perror("write target file");
        break;
      }
    }
    fat_close(fd0);
    close(fd1);
  }
}
