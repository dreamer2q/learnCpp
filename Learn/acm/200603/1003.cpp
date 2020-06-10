/*
 * File Created: Tuesday, 9th June 2020 11:21:08 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 9th June 2020 11:58:31 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

class Point {
public:
    int x, y;

    static Point from(istream& is) {
        int x, y;
        is >> x >> y;
        return Point(x, y);
    }

public:
    Point(int x, int y) : x(x), y(y){};
    friend Point operator-(const Point& lhs, const Point& rhs) {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }
};

class Vector {
public:
    int x, y;

public:
    Vector(const Point& p) : x(p.x), y(p.y) {}
    Vector(int x, int y) : x(x), y(y) {}
    friend int operator*(const Vector& v1, const Vector& v2) {
        return v1.x * v2.y - v2.x * v1.y;
    }
};

int main() {
    int n;
    while (cin >> n && n) {
        vector<Point> vp;
        for (int i = 0; i < n; i++) {
            vp.push_back(Point::from(cin));
        }
        vector<Vector> v;
        for (int i = 1; i <= n; i++) {
            auto tmp = vp[i % vp.size()] - vp[i - 1];
            v.push_back(tmp);
        }
        bool convex = true;
        for (int i = 1; i <= n; i++) {
            auto ro = v[i - 1] * v[i % v.size()];
            if (ro < 0) {
                convex = false;
                break;
            }
        }
        cout << (convex ? "convex" : "concave") << endl;
    }
    return 0;
}