#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define ERROR_EXIT(msg)                                       \
  do {                                                        \
    fprintf(stderr, msg ": %d %s\n", errno, strerror(errno)); \
    exit(errno);                                              \
  } while (0)

#define SERV_ADDR INADDR_ANY
#define SERV_PORT 6666

int main() {
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1) ERROR_EXIT("create socket");

  struct sockaddr_in servaddr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = htonl(SERV_ADDR),
      .sin_port = htons(SERV_PORT),
  };

  if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
    ERROR_EXIT("bind socket");
  }

  if (listen(listenfd, 10) == -1) ERROR_EXIT("listen socket");

  printf("server listening on :%d\n", SERV_PORT);

  for (;;) {
    struct sockaddr_in clntaddr;
    int clntlen;
    int connfd = accept(listenfd, (struct sockaddr*)&clntaddr, &clntlen);
    if (connfd == -1) {
      perror("accept client socket");
      continue;
    }
    printf("client connected: %d\n", connfd);

    char buffer[1024];
    int size = recv(connfd, buffer, sizeof(buffer), 0);
    buffer[size] = '\0';

    printf("recv %d bytes from %s: %s", size, inet_ntoa(clntaddr.sin_addr),
           buffer);
    close(connfd);
  }
  close(listenfd);

  return 0;
}
