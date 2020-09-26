/**
 * 
 *  friend 函数demo
 *  2020年3月31日
 * by dreamer2q
 * 
 */

#include <iostream>

using namespace std;

//前置声明，为了friend函数，可以访问到两个类内成员
class Boat;
class Car;

class Boat {
   public:
    Boat(double weight) : weight(weight) {
        cout << "new boat" << endl;
    }

    friend double totalWeight(const Boat& boat, const Car& car);

   private:
    const double weight;
};

class Car {
   public:
    Car(double w) : weight(w) {
        cout << "new car" << endl;
    }

    friend double totalWeight(const Boat& boat, const Car& car);

   private:
    const double weight;
};

double totalWeight(const Boat& boat, const Car& car) {
    return boat.weight + car.weight;
}

int main() {
    Car car(100);
    Boat boat(200);

    cout << "totalweight: " << totalWeight(boat, car) << endl;

    return 0;
}

/*

output:
new car
new boat
totalweight: 300

*/
