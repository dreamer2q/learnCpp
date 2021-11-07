#include <iostream>

using namespace std;

int x = 5, y = 7;

void myFunction() {
    int y = 10;
    cout << "x from myFunction " << x << endl;
    //这里的y被是函数内部的y，外部的y被覆盖的，不可见。
    cout << "y from myFunction " << y << endl;
}

int main() {
    //这里的x,y都是全局变量的x,y
    cout << "x from main " << x << endl;
    cout << "y from main " << y << endl;
    myFunction();
    cout << "back from myFunction" << endl;

    cout << "x from main " << x << endl;
    cout << "y from main " << y << endl;
    return 0;
}
/*

输出：
x from main 5
y from main 7
x from myFunction 5
y from myFunction 10
back from myFunction
x from main 5
y from main 7

*/
