/*
 * File Created: Tuesday, 23rd June 2020 10:40:32 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 23rd June 2020 11:58:08 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
#include <cmath>

using namespace std;

class Point {
    int x, y;

public:
    Point(int a = 0, int b = 0) : x(a), y(b){};
    int GetX() {
        return x;
    }
    int GetY() {
        return y;
    }
    void Print() {
        cout << "[" << x << "," << y << "]";
    }
};

class Line : public Point {
public:
    Line(int x1, int y1, int x2, int y2) : Point(x1, y1), endPoint(Point(x2, y2)) {}

    void Print() {
        cout << "开始点:";
        Point::Print();
        cout << ",结束点:";
        endPoint.Print();
    }
    double Length() {
        int x = Point::GetX() - endPoint.GetX();
        int y = Point::GetY() - endPoint.GetY();
        return sqrt(x * x + y * y);
    }

private:
    Point endPoint;
};

int main() {
    Line line(1, 1, 10, 10);
    cout << "line的";
    line.Print();
    cout << "\nline的长度:" << line.Length() << endl;
    return 0;
}
