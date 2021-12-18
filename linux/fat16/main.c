#include "color.h"
#include "filesys.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <unistd.h>
#include "common.h"
#include "cmd.h"

// 函数声明
void openEditor(const char *filename);
void eval(const char *cmd);

void print_motd() {
  char cwd[BUFSIZ];
  getcwd(cwd, BUFSIZ);
  printf("*** FATSYS BLOCK INFORMATION ***\n");
  printf("%s\n", fat_blkinfo()->info);
  printf("********************************\n\n");
  printf("workdir: %s\n", cwd);
  printf("built at: %s %s\n", __DATE__, __TIME__);
  printf("gcc version: %s\n", __VERSION__);
  printf("\n");
}

int builtin_ver(struct cmd_arg *args) {
  printf("My Fat File System: %s\n", __VERSION__);
  return 0;
}

void print_ps(void) {
  char cwd[128];
  fat_getcwd(cwd, sizeof(cwd));
  printf(GREEN("%s") "> ", cwd);
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
