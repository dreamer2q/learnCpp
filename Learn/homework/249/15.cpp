
/**
 *  顶层const 与 底层const demo
 * 2020年3月31日
 * by dreamer2q
 *
 */

#include <iostream>

using namespace std;

int main() {
    int i = 1;
    int i2 = 2;

    int* const p1 = &i;  //这个是顶层const,也就是修饰自己的,所以定义的时候必须初始化，可以修改指针指向的内容，但是自身不能被修改。
    //p1 = &i2; //错误，无法修改const 对象
    *p1 = 10;  //OK

    const int* p2 = &i;  //这是个底层的const,无法修改指针指向的内容，指针本身可以被修改。
    //*p2 = 20; //错误，无法修改const int对象
    p2 = &i2;  //OK

    return 0;
}
