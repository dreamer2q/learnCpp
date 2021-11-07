#include <stdio.h>
#include <pthread.h>

void* left_hand(void* args) { putchar('a'); }

void* right_hand(void* args) {
  putchar('m');
  putchar('i');
  putchar('n');
}

int main() {
  pthread_t lefthand, righthand;
  pthread_create(&righthand, NULL, right_hand, NULL);
  pthread_create(&lefthand, NULL, left_hand, NULL);

  pthread_join(righthand, NULL);
  pthread_join(lefthand, NULL);
  return 0;
}
