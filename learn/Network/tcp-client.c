#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("usage: %s host port\n", argv[0]);
    return -1;
  }

  int port = atoi(argv[2]);
  struct sockaddr_in servaddr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = inet_addr(argv[1]),
      .sin_port = htons(port),
  };

  int servfd = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(servfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
    perror("connect");
    return errno;
  }

  char buffer[1024];

  printf("%s < ", argv[1]);
  fgets(buffer, sizeof buffer, stdin);
  int sentlen = send(servfd, buffer, strlen(buffer), 0);
  if (sentlen < 0) {
    perror("sent failed");
    return -1;
  }

  int recvlen = recv(servfd, buffer, sizeof(buffer), 0);
  if (recvlen > 0) {
    printf("> %s\n", buffer);
  }

  close(servfd);
  return 0;
}
