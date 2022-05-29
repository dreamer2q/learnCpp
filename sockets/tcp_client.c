#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

// TCP connect
// ip port
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("usage: %s ip port\n", *argv);
    return -1;
  }

  const char *host = argv[1];
  const char *portStr = argv[2];
  int port = atoi(portStr);
  struct sockaddr_in ipaddr = {
      .sin_family = AF_INET,  // ipv4,
      /**
       * htons是将整型变量从主机字节顺序转变成网络字节顺序，
       * 就是整数在地址空间存储方式变为高位字节存放在内存的低地址处。
       * 网络字节顺序是TCP/IP中规定好的一种数据表示格式，它与具体的CPU类型、操作系统等无关，
       * 从而可以保证数据在不同主机之间传输时能够被正确解释，网络字节顺序采用big-endian排序方式。
       */
      .sin_port = htons(port),
  };

  int sock = socket(AF_INET, SOCK_STREAM /*TCP*/, 0);
  if (sock < 0) {
    printf("socket create error\n");
    return -1;
  }

  if (inet_pton(AF_INET, host, &ipaddr.sin_addr) <= 0) {
    printf("invalid address\n");
    return -1;
  }

  printf("connect to %s: %d\n", argv[1], port);
  if (connect(sock, (struct sockaddr *)&ipaddr, sizeof(ipaddr)) < 0) {
    printf("unable to connect\n");
    return -1;
  }

  char buf[512];
  printf("%s < ", host);
  fgets(buf, sizeof buf, stdin);
  size_t sz = send(sock, buf, strlen(buf), 0);
  printf("write ok: %ld\n", sz);
  int res = recv(sock, buf, sizeof buf, 0);
  if (res > 0) {
    buf[res] = '\0';
    printf("response: %s\n");
  }
  close(sock);
  return 0;
}
