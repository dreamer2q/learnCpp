#include "color.h"
#include "filesys.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGV 32

#define compare(s1, cmp, s2) (strcmp(s1, s2) cmp 0)
#define branch(str) char *__arg = str, __arg_flag = 0;
#define entry(str) if (!__arg_flag && (__arg_flag = compare(str, ==, __arg)))
#define default_entry if (!__arg_flag)

void openEditor(const char *filename);

void print_motd() {
  char cwd[BUFSIZ];
  getcwd(cwd, BUFSIZ);
  printf("*** FATSYS BLOCK INFORMATION ***\n");
  printf("%s\n", ((struct block0 *)virtual_disk)->info);
  printf("********************************\n\n");
  printf("workdir: %s\n", cwd);
  printf("built at: %s %s\n", __DATE__, __TIME__);
  printf("gcc version: %s\n", __VERSION__);
  printf("\n");
}

void print_usage(const char *cmd, const char *opt) {
  // Usage: touch filename
  printf("Usage: %s filename", cmd);
}

void print_ps(void) { printf(GREEN("%s") "> ", current_dir.dirname); }

int parseline(char *buf, char *argv[]) {
  buf[strlen(buf) - 1] = ' ';
  while (*buf && (*buf == ' ')) {
    buf++;
  }

  char *delim;
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

void eval(const char *cmd) {
  char buf[BUFSIZ];
  char *argv[MAX_ARGV];
  strcpy(buf, cmd);
  int argc = parseline(buf, argv);

  if (argc == 0) return;

  branch(argv[0]) {
    entry("help") { printf("this is a help msg\n"); }
    entry("exit") {
      exitsys();
      printf("goodbye~\n");
      exit(0);
    }
    entry("ls") {
      int len;
      struct fcb_t *list = fat_list(&len);
      printf("Directory of %s \nTotal: %d\n\n", current_dir.dirname, len);
      for (int i = 0; i < len; i++) {
        if (list[i].use_state) {
          char datetime[BUFSIZ] = {0};
          sprintf(datetime, "%04d-%02d-%02d %02d:%02d",
                  fat_get_year(list[i].date), fat_get_month(list[i].date),
                  fat_get_day(list[i].date), fat_get_hour(list[i].time),
                  fat_get_minute(list[i].time), fat_get_second(list[i].time));
          if (list[i].attr & FAT_ATTR_DIR) {
            printf("%s\t<DIR>\t%s\n", datetime, list[i].filename);
          } else {
            printf("%s\t%-5d\t%s\n", datetime, list[i].length,
                   list[i].filename);
          }
        }
      }
    }
    entry("cd") {
      if (argc < 2) {
        print_usage("cd", "dirname");
      } else {
        fat_cd(argv[1]);
      }
    }
    entry("mkdir") {
      if (argc < 2) {
        print_usage("mkdir", "filename");
      } else {
        fat_mkdir(argv[1]);
      }
    }
    entry("rmdir") {
      if (argc < 2) {
        print_usage("rmdir", "filename");
      } else {
        fat_rmdir(argv[1]);
      }
    }
    entry("touch") {
      if (argc < 2) {
        print_usage("touch", "filename");
      } else {
        fat_create(argv[1]);
      }
    }
    entry("edit") {
      if (argc < 2) {
        print_usage("edit", "filename");
      } else {
        pid_t pid;
        if ((pid = fork()) != -1) {
          if (pid == 0) {  // child
            openEditor(argv[1]);
          } else {  // parent
            int status;
            assert(waitpid(pid, &status, 0) >= 0, "waitpid");
            printf("editor exited: %d\n", status);
          }
        }
      }
    }
    entry("cat") {
      if (argc < 2) {
        print_usage("cat", "filename");
      } else {
        char buf[128];
        int fd = fat_open(argv[1]);
        if (fd != -1) {
          int len;
          while ((len = fat_read(fd, buf, sizeof(buf))) > 0) {
            for (int i = 0; i < len; i++) {
              putchar(buf[i]);
            }
          }
          fat_close(fd);
        }
      }
    }
    entry("rm") {
      if (argc < 2) {
        print_usage("rm", "filename");
      } else {
        fat_delete(argv[1]);
      }
    }
    default_entry {
      // default
      printf("command: %s not found\n", argv[0]);
    }
  }
}

int main() {
  startsys();

  print_motd();

  char cmdline[BUFSIZ];
  for (;;) {
    print_ps();

    fgets(cmdline, BUFSIZ, stdin);
    if (feof(stdin)) {
      return 0;
    }

    eval(cmdline);
  }
}
