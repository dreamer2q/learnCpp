#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int child, i = 2;
  if ((child = fork()) == -1) {
    printf("fork error");
    exit(-1);
  }

  if (child == 0) {  // 父进程
    i = i + 3;
    printf("i=%d\n", i);
  }

  i = i + 5;
  printf("i=%d\n", i);

  return 0;
}
