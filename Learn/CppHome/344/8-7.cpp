/*
by dreamer2q

重载++，前缀&&h后缀

2020年5月12日
*/

#include <iostream>

using namespace std;

class Point {
public:
    Point(int x = 0, int y = 0) : px(x), py(y) {}

    //前缀++
    Point operator++() {
        doIncrease();
        return *this;
    }
    //后缀++
    Point operator++(int) {
        Point p = *this;
        doIncrease();
        return p;
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.px << ", " << p.py << ")" << endl;
        return os;
    }

private:
    //自增函数
    void doIncrease() {
        px++;
        py++;
    }
    int px, py;
};

int main() {
    Point p;

    cout << p++;
    cout << ++p;

    return 0;
}

//output
/*
(0, 0)
(2, 2)
*/