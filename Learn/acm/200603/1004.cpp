/*
 * File Created: Wednesday, 10th June 2020 12:19:02 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 16th June 2020 5:14:29 pm
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
    // friend Vector operator-(const Point& lhs, const Point& rhs);
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
    friend int dot(const Vector& v1, const Vector& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    friend double distancev(const Vector& v);
};

Vector operator-(const Point& lhs, const Point& rhs) {
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

double distancev(const Vector& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

double vCos(const Vector& v1, const Vector& v2) {
    auto d = dot(v1, v2);
    auto d1 = distancev(v1);
    auto d2 = distancev(v2);
    auto r = d1 * d2;
    return d / r;
}

bool isLeft(const Point& v1, const Point& v2, const Point& v3) {
    auto p1 = v2 - v1;
    auto p2 = v3 - v1;
    auto res = p1 * p2;
    return res > 0;
    // return p1 * p2 > 0;
    // return (v2 - v1) * (v3 - v1) > 0;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Point> pv;
        for (int i = 0; i < n; i++) {
            pv.push_back(Point::from(cin));
        }
        auto iter0 = min_element(pv.begin(), pv.end(), [](const Point& lhs, const Point& rhs) {
            return lhs.y < rhs.y;
        });
        auto p0 = Point(*iter0);
        pv.erase(iter0);
        for_each(pv.begin(), pv.end(), [&](Point& p) {
            p.x -= p0.x;
            p.y -= p0.y;
        });
        sort(pv.begin(), pv.end(), [=](const Point& p1, const Point& p2) {
            Point vx(1, 0);
            auto c1 = vCos(vx, p1);
            auto c2 = vCos(vx, p2);
            if (fabs(c1 - c2) < 1e-6) {
                return p1.x < p2.x;
            }
            return c1 > c2;
            // return vCos(vx, p1) > vCos(vx, p2) || distancev(p1) < distancev(p2);
        });

        stack<Point> sp;
        sp.push(Point(0, 0));
        sp.push(pv[0]);
        // sp.push(pv[1]);
        for (int i = 1; i < pv.size(); i++) {
            auto pi = pv[i];
            while (1) {
                auto p1 = sp.top();
                sp.pop();
                auto p0 = sp.top();
                sp.push(p1);
                if (isLeft(p0, p1, pi)) break;
                sp.pop();
            }
            sp.push(pi);
        }
        sp.push(Point(0, 0));
        double ans = 0.0;
        auto prev = sp.top();
        sp.pop();
        while (!sp.empty()) {
            auto curr = sp.top();
            sp.pop();
            ans += distancev(curr - prev);
            prev = curr;
        }
        printf("%.2lf\n", ans);
    }

    return 0;
}
