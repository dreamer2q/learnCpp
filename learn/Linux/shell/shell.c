#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DEBUG

#ifdef DEBUG
#define debug(block) \
  do block while (0)
#else
#define debug(block)
#endif

#define LEN(a) (sizeof(a) / sizeof(a[0]))

#define MAXLINE 512
#define MAXARGS 128

#define COLOR(color, msg) "\033[" #color "m" msg "\033[0m"
#define RED(msg) COLOR(31, msg)
#define GREEN(msg) COLOR(32, msg)
#define YELLO(msg) COLOR(33, msg)
#define BLUE(msg) COLOR(34, msg)

/**
 * 全局变量
 */
int exec_status;    // 前台进程返回状态
pid_t running_pid;  // running child pid
char **environ;

/*
 ** 共享内存
 */
// #define SHARE_MEM_SIZE 32
// int shmid;
// int* shared_status;

const char *VERSION = "0.1.1";
void print_version() { printf(GREEN("version") ": %s\n", VERSION); }

void unix_error(const char *msg) {
  int errnum = errno;
  fprintf(stderr, "%s (%d: %s)\n", msg, errnum, strerror(errnum));
  exit(EXIT_FAILURE);
}

void print_motd() {
  printf(GREEN("Linux My Shell\n"));
  print_version();

  debug({
    printf(YELLO("gcc version:") " %s\n", __VERSION__);
    printf(YELLO("built date:") " %s\n", __DATE__);
  });

  printf("\n");
}

const char *get_current_workdir() {
  static char workdir[BUFSIZ];
  getcwd(workdir, sizeof(workdir));
  return strrchr(workdir, '/') + 1;
}

void print_ps() {
  // print ps
  const char *cwd = get_current_workdir();
  if (exec_status != 0) {
    printf(RED("➜"));
  } else {
    printf(GREEN("➜"));
  }
  printf("  \e[1;32m%s\e[0m ", cwd);
  fflush(stdout);
}

int builtin_command(char *argv[]) {
  if (!strcmp(argv[0], "exit")) {
    exit(0);
  }
  if (!strcmp(argv[0], "&")) {
    return 1;
  }
  if (!strcmp(argv[0], "env")) {
    char **env = environ;
    while (*env) {
      printf("%s\n", *env);
      env++;
    }
    return 1;
  }
  if (!strcmp(argv[0], "cd")) {
    if (chdir(argv[1]) < 0) {
      exec_status = errno;
      perror("chdir");
    }
    return 1;
  }
  return 0;
}

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

  if (argc == 0) {
    return 1;
  }

  int bg;
  if ((bg = (*argv[argc - 1] == '&')) != 0) {
    argv[--argc] = NULL;
  }

  return bg;
}

void eval(char *cmdline) {
  char *argv[MAXARGS];
  char buf[MAXLINE];

  strcpy(buf, cmdline);
  int bg = parseline(buf, argv);
  if (argv[0] == NULL) {
    exec_status = -1;
    return;
  }

  if (builtin_command(argv)) {
    return;
  }

  pid_t pid;
  if ((pid = fork()) == 0) {
    // child process
    if (execvp(argv[0], argv) < 0) {
      printf("%s: command not found.\n", argv[0]);
      exit(-1);
    }
  }

  if (!bg) {
    running_pid = pid;
    if (waitpid(pid, &exec_status, 0) < 0) {
      unix_error("waitfg: waitpid error");
    } else {
      debug({
        printf("\n" YELLO("DEBUG:") " status=%d pid=%d", exec_status, pid);
        char **arg = argv;
        printf(" argv: ");
        while (*arg) {
          printf("%s ", *arg);
          arg++;
        }
        printf("\n");
      });
    }
    running_pid = 0;
  } else {
    printf("[BG] %d\n", pid);
  }
}

void signal_handler(int signo) {
  debug({ printf("\n(DEBUG) recv signal: %d\n", signo); });

  switch (signo) {
    case SIGINT: {
      // kill running child if possible
      if (running_pid) {
        int ret = kill(running_pid, SIGKILL);
        if (ret < 0) {
          perror("KILL");
        }
      } else {
        print_ps();
      }
    } break;
    case SIGCHLD: {
      int status;
      int pid = wait(&status);
      if (WIFEXITED(status)) {
        printf("[BG] %d: exited %d\n", pid, WEXITSTATUS(status));
      } else if (WIFSTOPPED(status)) {
        printf("[BG] %d: stopped %d\n", pid, WSTOPSIG(status));
      } else if (WIFSIGNALED(status)) {
        printf("[BG] %d: signaled by %d\n", pid, WTERMSIG(status));
      }
    } break;
    case SIGKILL:
    case SIGQUIT:
    case SIGTERM: {
      exit(-1);
    } break;
  }
}

void register_signal() {
  int signals[] = {SIGQUIT, SIGKILL, SIGTERM, SIGINT, SIGCHLD};
  for (int i = 0; i < LEN(signals); i++) {
    signal(signals[i], signal_handler);
  }
}

int main(int argc, char *argv[], char *env[]) {
  environ = env;
  register_signal();

  print_motd();

  debug({ printf("(DEBUG) pid: %d\n", getpid()); });

  char cmdline[MAXLINE];

  for (;;) {
    print_ps();

    fgets(cmdline, MAXLINE, stdin);
    if (feof(stdin)) {
      return 0;
    }

    eval(cmdline);
  }
}
