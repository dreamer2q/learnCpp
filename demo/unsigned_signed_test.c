#include <stdio.h>

int main() {
  unsigned int a = 6;
  char b = -3;
  printf("%d, %u\n", a + b, a + b);
  if ((a + b) > 0) {
    printf("yes\n");
  } else {
    printf("no\n");
  }
  return 0;
}
