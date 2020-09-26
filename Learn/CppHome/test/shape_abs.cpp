/*
 * File Created: Tuesday, 23rd June 2020 11:22:37 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 23rd June 2020 11:40:13 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
#include <deque>

using namespace std;

class Shape {
public:
    virtual void ShowArea(){};
};

class Circle : public Shape {
    double radius;

public:
    Circle(double r) : radius(r) {}
    void ShowArea() {
        cout << "Բ�������" << 3.14159 * radius * radius << endl;
    }
};

class Square : public Shape {
    double side;

public:
    Square(double s) : side(s) {}
    void ShowArea() {
        cout << "�����������" << side * side << endl;
    }
};

int main() {
    double r, s;
    cout << "������뾶��";
    cin >> r;
    cout << "�����������α߳���";
    cin >> s;
    deque<Shape*> ds = {
        new Circle(r),
        new Square(s),
    };
    for (auto beg = ds.begin(); beg != ds.end(); beg++) {
        (*beg)->ShowArea();
    }

    return 0;
}
