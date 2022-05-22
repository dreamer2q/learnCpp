#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_message_function(void *ptr) {
  char *message;
  message = (char *)ptr;
  printf("%s \n", message);
  return NULL;
}

int main() {
  pthread_t thread1, thread2;
  char *message1 = "Thread 1";
  char *message2 = "Thread 2";
  int iret1, iret2;

  /* Create independent threads each of which will execute function */

  iret1 =
      pthread_create(&thread1, NULL, print_message_function, (void *)message1);
  iret2 =
      pthread_create(&thread2, NULL, print_message_function, (void *)message2);

  printf("Thread 1 returns: %d\n", iret1);
  printf("Thread 2 returns: %d\n", iret2);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  exit(0);
}
