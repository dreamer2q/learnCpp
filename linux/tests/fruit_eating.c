#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

/**
 * 有一个盘子，可以放5个水果（苹果or桔子）。
 * 父亲每次向盘子随机放入一个水果（苹果or桔子），
 * 父亲放入水果的次数不少于11次。
 * 儿子只吃桔子，女儿只吃苹果。
 * 请编程使用信号量机制模拟解决此进程同步问题。
 * 打印信息包括盘子的情况、调度的情况以及父亲、儿子或者女儿执行的操作。
 */

sem_t taken;  // 盘子是否被占用（这个信号量是用来进行同步的）
sem_t empty;   // 盘中是否为空
sem_t orange;  // 橘子
sem_t apple;   // 苹果

const char* cc_apple = "\e[33m苹果\e[0m";
const char* cc_orange = "\e[34m橘子\e[0m";
const char* cc_father = "\e[35m爸爸\e[0m";
const char* cc_son = "\e[36m儿子\e[0m";
const char* cc_daughter = "\e[37m女儿\e[0m";

void* father(void* args) {
  while (1) {
    sem_wait(&empty);  // 等待空盘子
    sem_wait(&taken);  // 准备占用盘子
    int put_apple = rand() % 2;
    printf("%s占用了盘子，并放入了一个", cc_father);
    if (put_apple) {
      sem_post(&apple);
      printf(cc_apple);
    } else {
      sem_post(&orange);
      printf(cc_orange);
    }
    printf("后释放了盘子。\n");
    sem_post(&taken);  // 释放盘子
  }
}

void* son(void* args) {
  while (1) {
    sem_wait(&orange);
    sem_wait(&taken);
    printf("%s占用了盘子，并拿走了一个%s后，释放了盘子。\n", cc_son, cc_orange);
    sem_post(&taken);
    sem_post(&empty);
  }
}

void* daughter(void* args) {
  while (1) {
    sem_wait(&apple);
    sem_wait(&taken);
    printf("%s占用了盘子，并拿走了一个%s后，释放了盘子。\n", cc_daughter,
           cc_apple);
    sem_post(&taken);
    sem_post(&empty);
  }
}

void init() {
  sem_init(&empty,  // 需要初始的semaphore对象
           0,       // 本进程内部使用，不对其它进程共享
           5);      // 盘子初始为空
  sem_init(&orange, 0, 0);
  sem_init(&apple, 0, 0);
  sem_init(&taken, 0, 1);  // 初始状态盘子没有被占用
  srand(time(NULL));
}

void dispose() {
  // 释放信号量
  sem_destroy(&taken);
  sem_destroy(&empty);
  sem_destroy(&orange);
  sem_destroy(&apple);

  printf("sem disposed\n");
}

int main() {
  init();

  pthread_t threads[3];
  void* (*funcs[])(void*) = {father, son, daughter};
  for (int i = 0; i < 3; i++) {
    printf("creat thread %d: %x\n", i, funcs[i]);
    pthread_create(&threads[i], NULL, funcs[i], NULL);
  }
  for (int i = 0; i < 3; i++) {
    printf("join thread %d\n", i);
    pthread_join(threads[i], NULL);
  }

  dispose();
  return 0;
}
