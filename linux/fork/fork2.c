#include <stdio.h>
#include <unistd.h>

int main() {
  int cid = fork();
  if (cid < 0) {
    perror("fork");
    return cid;
  }

  if (cid == 0) {
    fprintf(stderr, "m");
    fprintf(stderr, "i");
    fprintf(stderr, "n");
  } else {
    fprintf(stderr, "a");
  }
  sleep(1);
  return 0;
}
