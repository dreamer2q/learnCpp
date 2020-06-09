#include <bits/stdc++.h>

using namespace std;

class Vector {
   public:
    int x, y;

   public:
    Vector(int x, int y) : x(x), y(y) {}
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
    return fabs(0.5 * res);
}
double Area(const Vector& v1, const Vector& v2) {
    return 0.5 * (v1 * v2);
}

double Center3(int a, int b) {
    return (a + b + 0.0) / 3.0;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Vector> v;
        for (int i = 0; i < n; i++) {
            int x, y;
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
            Xc += Center3(v[i - 1].x, v[i % n].x) * va[i - 1];
        }
        Xc /= (n * area);
        for (int i = 1; i <= n; i++) {
            Yc += Center3(v[i - 1].y, v[i % n].y) * va[i - 1];
        }
        Yc /= (n * area);
        printf("%.2lf %.2lf\n", Xc, Yc);
    }
    return 0;
}