#include <stdio.h>
#include <stdlib.h>

void why_here() {
  fprintf(stderr, "why ur here? :)");
  exit(0);
}

void f() {
  int buff[1];
  int* p = &buff[0];
  *p = ((int (*)())why_here)();
}

int main() {
  f();
  return 0;
}
