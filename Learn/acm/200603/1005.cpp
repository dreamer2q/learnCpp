/*
 * File Created: Saturday, 20th June 2020 12:54:22 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Saturday, 20th June 2020 2:17:14 am
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

    Point(int x, int y) : x(x), y(y){};

    double distance(const Point& p) const {
        auto x2 = (x - p.x) * (x - p.x);
        auto y2 = (y - p.y) * (y - p.y);
        return sqrt(x2 * x2 + y2 * y2);
    }
};

class Vector {
public:
    int x, y;

    Vector(const Point& p) : x(p.x), y(p.y) {}
    Vector(int x, int y) : x(x), y(y) {}

    double length() const {
        return sqrt(x * x + y * y);
    }

    double angle(const Vector& v) const {
        auto d = *this * v;
        auto l1 = this->length();
        auto l2 = v.length();
        auto c = d / (l1 * l2);
        return acosh(c);
    }

    bool leftOf(const Vector& v) {
        return (*this ^ v) > 0;
    }

    friend int operator*(const Vector& v1, const Vector& v2);
    friend int operator^(const Vector& v1, const Vector& v2);
};
//点乘
int operator*(const Vector& v1, const Vector& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
//叉乘
int operator^(const Vector& v1, const Vector& v2) {
    return v1.x * v2.y - v2.x * v1.y;
}
//向量
Vector operator-(const Point& lhs, const Point& rhs) {
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

vector<Point> grahamScan(const vector<Point>& input) {
    auto min_iter = min_element(input.begin(), input.end(), [](const Point& lhs, const Point& rhs) {
        return lhs.y < rhs.y;
    });
    vector<Point> points(input.begin(), min_iter);
    points.insert(points.end(), min_iter + 1, input.end());
    //根据角度排序
    sort(points.begin(), points.end(), [&min_iter](const Point& p1, const Point& p2) {
        auto& base = *min_iter;
        auto v0 = Vector(1, 0);
        auto v1 = p1 - base;
        auto v2 = p2 - base;
        auto ang1 = v0.angle(v1);
        auto ang2 = v0.angle(v2);
        if (fabs(ang1 - ang2) < 1e-6) {
            return v1.x < v2.x;
        }
        return ang1 < ang2;
    });
    stack<Point> sp;
    sp.push(*min_iter);
    sp.push(points[0]);
    for (int i = 1; i < points.size(); i++) {
        const auto& pi = points[i];
        while (1) {
            auto p1 = sp.top();
            sp.pop();
            auto p0 = sp.top();
            sp.push(p1);
            auto v1 = p1 - p0;
            auto v2 = pi - p0;
            if (v2.leftOf(v1)) {
                break;
            }
            sp.pop();
        }
        sp.push(pi);
    }
    sp.push(*min_iter);
    vector<Point> ret;
    while (!sp.empty()) {
        ret.push_back(sp.top());
        sp.pop();
    }
    return ret;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Point> vp;
        for (int i = 0; i < n; i++) {
            vp.push_back(Point::from(cin));
        }
        auto res = grahamScan(vp);
        double ans = 0;
        for (int i = 1; i < res.size(); i++) {
            ans += res[i].distance(res[i - 1]);
        }
        cout << ans << endl;
    }
    return 0;
}
