#include <stdio.h>

int main() {
  int a = 0x01;
  char* b = (char*)&a;
  printf("this CPU is %s endian.\n", b ? "little" : "big");
  return 0;
}
