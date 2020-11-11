#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init() {
    //初始化随机数种子
    srand(time(NULL));
}

int main() {
    init();

    printf("Number guessing game, in which the computer generates a random number between 1 and 100, you must input the exact number to win the game!\n");
    while (1) {
        
    }
    return 0;
}