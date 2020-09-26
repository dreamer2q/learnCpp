/* 
 *  static 在函数内部的demo
 *  2020年3月31日
 * by dreamer2q
 * 
 */

#include <iostream>

using namespace std;

int fnl() {
    //这里就是实打实的定义了，可以进行初始化
    //这个变量的生命周期就和全局变量一样长，只是它的作用域被限制在一个函数里面。
    static int _i = 0;
    //每次都会加一
    return ++_i;
}

int main() {
    for (int i = 0; i < 10; i++) {
        cout << fnl() << endl;
    }
    return 0;
}

/*

output:

1
2
3
4
5
6
7
8
9
10

*/