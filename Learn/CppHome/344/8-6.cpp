/*
by dreamer2q

�ӿڵĶ�����ʵ��

2020��5��12��

*/

#include <iostream>
using namespace std;

class Shape {
public:
    //���麯��������shape�Ľӿ�
    virtual double getArea() = 0;
    virtual double getPrime() = 0;
};

//ʵ��Shape�ӿ�
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

//ʵ��Shape�ӿ�
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

//���ߺ���,����ʹ��
template <class T>
void _print(T arg) {
    cout << arg << " ";
}

template <class... Args>
void log(Args... args) {
    int arr[] = {(_print(args), 0)...};
    cout << endl;
}

//���Ժ���
void ensure(bool condition, string msg) {
    if (condition) {
        log("���Գɹ�");
    } else {
        log("����ʧ��", msg);
    }
}

//����
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