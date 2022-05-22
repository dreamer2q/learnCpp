#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 1024

#define exitby(msg)                                              \
  do {                                                           \
    fprintf(stderr, "%s(%d): %s: " msg "\n", __FILE__, __LINE__, \
            strerror(errno));                                    \
    exit(errno);                                                 \
  } while (0)

#define assert(cb, msg) \
  do {                  \
    if (!(cb)) {        \
      exitby(msg);      \
    }                   \
  } while (0)

int main() {
  printf("Hello, world");

  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(listenfd != -1, "create listen socket");

  struct sockaddr_in servaddr = {
      .sin_family = AF_INET,
      .sin_port = htons(6666),
      .sin_addr.s_addr = INADDR_ANY,
  };
  int b = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
  assert(b != -1, "bind address");

  assert(listen(listenfd, 10) != -1, "listen");

  printf("server listening at :6666\n");

  for (;;) {
    struct sockaddr_in clntaddr;
    socklen_t clntlen;
    int clntfd = accept(listenfd, (struct sockaddr*)&clntaddr, &clntlen);
    if (clntfd == -1) {
      printf("accept client error: %s\n", strerror(errno));
      continue;
    }
    printf("accept client: %s:%d\n", inet_ntoa(clntaddr.sin_addr),
           ntohs(clntaddr.sin_port));

    char buff[BUFSIZE];
    int recvlen = recv(clntfd, buff, sizeof(buff), 0);
    if (recvlen > 0) {
      printf("recv: %s\n", buff);
    }
    close(clntfd);
  }

  return 0;
}
