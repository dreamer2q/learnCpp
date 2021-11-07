/**
 *  new 与 delete 简单使用
 * 
 * 2020年3月31日
 * 
 * by dreamer2q
 * 
 * 
 */

#include <iostream>

using namespace std;

class simpleCircle {
   public:
    simpleCircle(int radius) {
        m_itsRadius = new int(radius);
    }
    ~simpleCircle() {
        delete m_itsRadius;
    }

    double getArea() {
        int radius = *m_itsRadius;
        return PI * radius * radius;
    }

    int getRadius() {
        return *m_itsRadius;
    }
    void setRadius(int r) {
        *m_itsRadius = r;
    }

   private:
    int* m_itsRadius;
    const double PI = 3.14159;
};

int main() {
    simpleCircle r(10);



    cout << "radius: " << r.getRadius() << endl;
    cout << "area: " << r.getArea() << endl;
    r.setRadius(20);
    cout << "radius: " << r.getRadius() << endl;
    cout << "area: " << r.getArea() << endl;

    return 0;
}