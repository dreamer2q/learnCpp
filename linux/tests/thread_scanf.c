#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/**
 ** scanf 的执行并不会阻塞整个程序，两个scanf同时使用也没有问题
 */
void *scan_handler(void *_) {
  for (int i = 0; i < 3; i++) {
    char str[BUFSIZ];
    printf("input(%d): ", (int)_);
    scanf("%s", str);
    printf("echo(%d): %s\n", (int)_, str);
  }
  return NULL;
}

void *print_handler(void *_) {
  for (int i = 0;; i++) {
    sleep(1);
    printf("print_handler: %d\n", i);
  }
  return NULL;
}

int main() {
  pthread_t thr_scan1, thr_scan2, thr_print;

  pthread_create(&thr_scan1, NULL, scan_handler, (void *)1);
  pthread_create(&thr_scan2, NULL, scan_handler, (void *)2);
  pthread_create(&thr_print, NULL, print_handler, NULL);

  pthread_join(thr_scan1, NULL);
  pthread_join(thr_scan2, NULL);
  pthread_join(thr_print, NULL);

  return 0;
}
