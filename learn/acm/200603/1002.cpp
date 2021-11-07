/*
 * File Created: Tuesday, 9th June 2020 11:06:25 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 9th June 2020 11:09:38 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

class Vector {
public:
    double x, y;

public:
    Vector(double x, double y) : x(x), y(y) {}
    friend double operator*(const Vector& v1, const Vector& v2) {
        return v1.x * v2.y - v2.x * v1.y;
    }
};

double Area(const vector<Vector>& v) {
    double res = 0;
    for (int i = 1; i <= v.size(); i++) {
        res += v[i - 1] * v[i % v.size()];
    }
    return 0.5 * res;
}

// double Area(const Vector& v1, const Vector& v2) {
//     return 0.5 * (v1 * v2);
// }

int main() {
    int n;
    while (cin >> n && n) {
        vector<Vector> v;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            v.push_back(Vector(x, y));
        }
        printf("%.1lf\n", Area(v));
    }

    return 0;
}