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

struct Point {
    int x, y;
};

double Area(const vector<Vector>& v) {
    double res = 0;
    for (int i = 1; i <= v.size(); i++) {
        res += v[i - 1] * v[i % v.size()];
    }
    return res;
}
double Area(const Vector& v1, const Vector& v2) {
    return (v1 * v2);
}

/*
题目输出要求有一句exactly two digits after the decimal point (0.005 rounds up to 0.01)。
而直接使用%.2f是会有带来误差的，因为其自带的是“伪四舍五入”，也就是说：

2.54 -> 2.5
2.55 -> 2.5
2.56 -> 2.6

即当题目要求保留2位小数且四舍五入时，应将自己的结果加上0.001，保证当结果为2.555时能进位。
*/

int main() {
    // printf("%.2lf %.2lf", -0.0 + 0.001, 0.0);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Vector> v;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            v.push_back(Vector(x, y));
        }
        double area = Area(v);
        vector<double> va;
        for (int i = 1; i <= n; i++) {
            va.push_back(Area(v[i - 1], v[i % n]));
        }
        double Xc = 0, Yc = 0;
        for (int i = 1; i <= n; i++) {
            Xc += (v[i - 1].x + v[i % n].x) * va[i - 1];
        }
        Xc /= area * 3;
        for (int i = 1; i <= n; i++) {
            Yc += (v[i - 1].y + v[i % n].y) * va[i - 1];
        }
        Yc /= area * 3;
        printf("%.2lf %.2lf\n", Xc + 0.001, Yc + 0.001);
    }
    return 0;
}