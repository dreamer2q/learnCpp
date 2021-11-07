/*
by dreamer2q

接口的定义与实现

2020年5月12日

*/

#include <iostream>
using namespace std;

class Shape {
public:
    //纯虚函数，定义shape的接口
    virtual double getArea() = 0;
    virtual double getPrime() = 0;
};

//实现Shape接口
class Rectangle : public Shape {
public:
    Rectangle(int w, int h) : width(w), height(h) {}

    double getArea() {
        return width * height;
    }

    double getPrime() {
        return 2 * (width + height);
    }

private:
    int width, height;
};

//实现Shape接口
class Circle : public Shape {
public:
    Circle(int r) : radius(r) {}

    double getArea() {
        return pi * radius * radius;
    }

    double getPrime() {
        return 2 * pi * radius;
    }

private:
    int radius;
    double pi = 3.14159;
};

//工具函数,测试使用
template <class T>
void _print(T arg) {
    cout << arg << " ";
}

template <class... Args>
void log(Args... args) {
    int arr[] = {(_print(args), 0)...};
    cout << endl;
}

//测试函数
void ensure(bool condition, string msg) {
    if (condition) {
        log("测试成功");
    } else {
        log("测试失败", msg);
    }
}

//测试
void test() {
    Rectangle rc(1, 2), rc2(2, 2);
    ensure(rc.getArea() - 2 < 1e-6, "rc getArea error");
    ensure(rc.getPrime() - 6 < 1e-6, "rc getPrime error");
    ensure(rc2.getArea() - 4 < 1e-6, "rc getArea error");
    ensure(rc2.getPrime() - 8 < 1e-6, "rc getPrime error");

    Circle c1(1), c2(2);
    ensure(c1.getArea() - 3.14159 < 1e6, "c1 getArea error");
    ensure(c1.getPrime() - 2 * 3.14159 < 1e6, "c1 getPrime error");
    ensure(c2.getArea() - 4 * 3.14159 < 1e6, "c2 getArea error");
    ensure(c2.getPrime() - 4 * 3.14159 < 1e6, "c2 getPrime error");
}
int main() {
    test();
    return 0;
}