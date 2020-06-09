
#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
};

class Line;

class Vector {
   public:
    Vector(const Line& l);
    friend double operator*(const Vector& v1, const Vector& v2) {
        return v1.p.x * v2.p.y - v2.p.x * v1.p.y;
    }

   private:
    Point p;
};

class Line {
   public:
    Line(const Point p1, const Point p2) : p1(p1), p2(p2) {}
    static Line read(istream& is) {
        Point p1, p2;
        cin >> p1.x >> p1.y >> p2.x >> p2.y;
        return Line(p1, p2);
    }

    bool intersectWith(const Line& line) const {
        Line l13(p1, line.p1);
        Line l14(p1, line.p2);
        Vector v12(*this);
        Vector v13(l13);
        Vector v14(l14);

        double d1 = v12 * v13;
        double d2 = v12 * v14;
        bool res = false;
        if (d1 * d2 < 0) {
            res = true;
        } else if (d1 == 0 && inLine(line.p1)) {
            res = true;
        } else if (d2 == 0 && inLine(line.p2)) {
            res = true;
        }
        return res;
    }

    bool inLine(const Point& p) const {
        return min(p1.x, p2.x) <= p.x && p.y <= max(p1.x, p2.x) &&
               min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y);
    }

    friend Vector;

   private:
    Point p1, p2;
};

Vector::Vector(const Line& l) {
    p.x = l.p2.x - l.p1.x;
    p.y = l.p2.y - l.p1.y;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Line> lines;
        for (int i = 0; i < n; i++) {
            lines.push_back(Line::read(cin));
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans += (lines[i].intersectWith(lines[j]) && lines[j].intersectWith(lines[i]));
            }
        }
        cout << ans << endl;
    }
    return 0;
}