
#include <iostream>
#include <string>

using namespace std;

class Circle {
   public:
    Circle(double radius) : radius(radius) {
        cout << "Circle Constructor" << endl;
    }

    double getArea() {
        return radius * radius * Pi;
    }

   private:
    double radius = 0;
    const double Pi = 3.14159;
};

int main() {
    Circle ro(10);
    cout << "Area: " << ro.getArea() << endl;

    return 0;
}