#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//常量
const char* tip = "Input: ";
const char* tipBig = "It's bigger\n";
const char* tipSmall = "It's small\n";
const char* tipSuccess = "Bingo, you got it right\n";
const char* promote = "Will you try again (y/N): ";

// global variables
int answer;
int times;

void init() {
  //初始化随机数种子
  srand(time(NULL));
}

void initGame() {
  //产生一个随机数
  answer = rand() % 100 + 1;
  times = 0;
}

//游戏的主逻辑
void loopGame() {
  int user_input;
  while (1) {
    printf(tip);
    if (scanf("%d", &user_input) != 1) {
      getchar();
      continue;
    }
    times++;
    if (user_input > answer) {
      printf(tipBig);
    } else if (user_input < answer) {
      printf(tipSmall);
    } else {
      printf(tipSuccess);
      break;
    }
  }
}

//结束游戏
void overGame() {
  char choice;
  printf("In this round, you have tried %d %s, great job\n", times,
         times > 1 ? "times" : "time");
  printf(promote);
  choice = getchar();
  if (choice == 'N' || choice == 'n') {
    exit(0);
  }
}

int main() {
  init();

  printf(
      "Number guessing game,\n in which the computer generates a random number "
      "between 1 and 100, \nyou must input the exact number to win the "
      "game!\n");
  while (1) {
    initGame();
    loopGame();
    overGame();
  }
  return 0;
}
