#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define MAXCHNUM 3
#define FILL "fill"
#define EMPTY "empty"
#define MUTEX "mutex"
const char TESTSIZE[20] = "--getsize";
const char FULLWRITE[20] = "--full";
const char EMPTYREAD[20] = "--empty";

int fd[2];
char buf[1024] = "hello world";
char read_buf[1024] = {0};
int get_size_flag = 0, cnt = 0, full_write_flag = 0, empty_read_flag = 0;
sem_t *fill = NULL, *empty = NULL, *mutex = NULL;

// 获取管道的大小
int get_full_pipe_size() {
  int size = -2;
  size = fcntl(fd[0], F_GETPIPE_SZ);  // 获取管道大小
  if (size == -1) {
    printf("error: fcntl get size failed\n");
  } else if (size >= 0) {
    return size;
  }

  return -1;
}

// 获取管道已经使用的大小
int get_used_pipe_size() {
  int size = -1;
  if (ioctl(fd[1], FIONREAD, &size) == -1)  // 获取管道已经使用的大小
    printf("failed to get use size of pipe\n");
  return size;
}

// 将管道写满
void set_full() {
  // 管道设置为非阻塞
  int mode = fcntl(fd[1], F_GETFL);
  mode = O_NONBLOCK;
  fcntl(fd[1], F_SETFL, mode);

  for (int i = 0;; i++) {
    if (write(fd[1], "a", sizeof(char)) == -1) {
      printf("-----------------------------------------\n");
      printf("PIPE IS FULL AND SIZE OF PIPE IS %d bytes\n", cnt);
      printf("-----------------------------------------\n");
      break;
    }
    cnt++;
  }
  // 还原为异步阻塞
  fcntl(fd[1], F_SETFL, mode | O_ASYNC);
}

int main(int argc, char const *argv[]) {
  // choose func
  for (int i = 1; i < argc; i++) {
    printf("%s\n", argv[i]);
    if (strcmp(argv[i], TESTSIZE) == 0) {
      printf("test size of pipe\n");
      get_size_flag = 1;
    } else if (strcmp(argv[i], FULLWRITE) == 0) {
      full_write_flag = 1;
      printf("test full write\n");
    } else if (strcmp(argv[i], EMPTYREAD) == 0) {
      empty_read_flag = 1;
      printf("test empty read\n");
    }
  }
  // create pipe
  if (pipe(fd) == -1) {
    printf("failed to create pipe\n");
  }

  /**
   * test the size of pipe
   */
  int full_size_of_pipe = get_full_pipe_size();
  if (get_size_flag) {
    printf("size of pipe is %d\n", full_size_of_pipe);
    exit(0);
  }

  // 在管道满时写入，先写满
  if (full_write_flag) {
    set_full();
    // 设置管道为非阻塞
    fcntl(fd[1], F_SETFL, fcntl(fd[1], F_GETFL) | O_NONBLOCK);
  }

  /**
   * parent
   */
  int flag = 0;
  pid_t pid[MAXCHNUM];
  // 信号量
  if ((mutex = sem_open(MUTEX, O_CREAT | O_RDWR, 0777, 1)) == SEM_FAILED) {
    printf("failed to create sem mutex\n");
    return 0;
  }

  // 创建三个子进程
  for (int i = 0; i < MAXCHNUM; i++) {
    if ((flag = (pid[i] = fork())) == 0) {
      break;
    }
  }

  if (flag) {
    // wait child processes to exit
    while (waitpid(-1, NULL, 0) > 0)
      ;
    printf("---------------------\n");
    printf("parent begin to read\n");
    int mode = fcntl(fd[0], F_GETFL);
    fcntl(fd[0], F_SETFL, mode | O_NONBLOCK);
    if (read(fd[0], read_buf, sizeof(read_buf)) == -1) {
      printf(
          "failed read from pipe, pipe used size %d bytes, total size  %d "
          "bytes\n",
          get_used_pipe_size(), full_size_of_pipe);
    } else {
      printf("read: %s\n", buf);
      int size = get_used_pipe_size();
      printf(
          "parent: read: read size: %ld, pipe used size : %d bytes, remain "
          "%d bytes\n",
          sizeof(buf), size, full_size_of_pipe - size);
    }
    sem_close(empty);
    sem_unlink(MUTEX);
    printf("parent read done\n");
    printf("---------------------\n");
  } else {
    if (empty_read_flag) {
      ;  // 不写 直接退出
    } else if (full_write_flag) {
      sem_wait(mutex);
      if (write(fd[1], buf, sizeof(buf)) == -1) {
        printf(
            "failed to write pipe, pipe used size %d bytes, total size  %d "
            "bytes\n",
            get_used_pipe_size(), full_size_of_pipe);
      }
      sem_post(mutex);
    } else {  // normal
      sem_wait(mutex);
      write(fd[1], buf, sizeof(buf));
      int size = get_used_pipe_size();
      printf("child: %d, write: pipe used size : %d bytes, remain %d bytes\n",
             getpid(), size, full_size_of_pipe - size);
      sem_post(mutex);
    }
    printf("child: %d exit\n", getpid());
  }
  return 0;
}
