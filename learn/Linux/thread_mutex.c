#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *functionC();
int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
  int rc1, rc2;
  pthread_t thread1, thread2;

  /* Create independent threads each of which will execute functionC */

  if ((rc1 = pthread_create(&thread1, NULL, &functionC, NULL))) {
    printf("Thread creation failed: %d\n", rc1);
  }

  if ((rc2 = pthread_create(&thread2, NULL, &functionC, NULL))) {
    printf("Thread creation failed: %d\n", rc2);
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("the counter is %d\n", counter);
  exit(0);
}

void *functionC() {
  int i;
  for (i = 0; i < 200; i++) {
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
