/**
 * 类的接口与基础
 * 
 * by dreamer2q 
 * 2020年4月14日
 * 
 */

#include <iostream>

/**
 * Shape 是一个抽象类，它提供了计算面积的接口
 */
class Shape {
   public:
    virtual double getArea() = 0;
};

/**
 *  Rectangle 实现了Shape的接口，代表矩形
 */
class Rectangle : Shape {
   public:
    Rectangle(int width = 0, int height = 0) : m_width(width), m_height(height) {}

    //拷贝构造函数
    Rectangle(const Rectangle& rect) : m_width(rect.m_height), m_height(rect.m_height) {
        std::cout << "Rectangle 拷贝构造函数" << std::endl;
    }

    double getArea() { return m_width * m_height; }

    int getWidth() { return m_width; }
    void setWidth(int w) { m_width = w; }
    int getHeight() { return m_height; }
    void setHeight(int h) { m_height = h; }

   protected:
    int m_width;
    int m_height;
};

/**
 * Square 实现了Shape接口，基础于Rectangle  
 */

class Square : protected Rectangle {
   public:
    Square(int w) : Rectangle(w, w) {}
    Square(const Square& sq) : Rectangle(sq) {
        std::cout << "Square 拷贝构造函数" << std::endl;
    }

    double getArea() { return Rectangle::getArea(); }
    int getWidth() { return this->m_height; }
    void setWidth(int w) { this->m_height = this->m_width = w; }
};

/**
 *  Circle 实现了Shape接口，圆形类
 *
 */
class Circle : public Shape {
   public:
    Circle(int radius = 0) : m_radius(radius) {}
    Circle(const Circle& c) : Circle(c.m_radius) {
        std::cout << "Circle 拷贝构造函数" << std::endl;
    }
    double getArea() { return PI * m_radius * m_radius; }
    int getRadius() { return m_radius; }
    void setRadius(int r) { m_radius = r; }

    Circle& operator=(const Circle& c) = delete;

   private:
    int m_radius;
    const double PI = 3.14159;
};

using namespace std;

int main() {
    Shape* s = new Circle(10);
    cout << s->getArea() << endl;
    Circle c = Circle(1);
    cout << c.getArea() << endl;

    Rectangle rect(5, 10);
    cout << rect.getArea() << endl;

    Square sq = Square(1);
    cout << sq.getArea() << endl;

    Square q = sq;
    Square t(2);
    cout << q.getArea() << endl;

    return 0;
}

/**
输出
314.159
3.14159
50
1
Rectangle 拷贝构造函数
Square 拷贝构造函数
1
*/