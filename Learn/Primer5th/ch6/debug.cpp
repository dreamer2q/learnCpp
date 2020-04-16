#include <iostream>

using namespace std;

//#define NDEBUG
//use NDEBUG to disable assert() check
#include <cassert>

#include "myheader.h"

int main() {
    printf("%s", 10);

    debug_msg("this is a debug message");

    printf("Assert Test\n");
    printf("When assert express succeed\n");
    assert(1 == 1);
    printf("When the express in the assert macro fails\n");

    assert(1 == 2);

    printf("can not be executed here\n");
    return 0;
}
