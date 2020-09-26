/*
2020年4月30日

by dreamer2q
*/

#include <iostream>

using namespace std;

class Object {
   public:
    Object(int w) : weight(w) {
        cout << "Object construct" << endl;
    };
    ~Object() {
        cout << "Object destruct" << endl;
    }
    void setWeight(int w) {
        weight = w;
    }
    int getWeight() {
        return weight;
    }

    friend ostream& operator<<(ostream& os, const Object& o) {
        os << "Object weight " << o.weight << endl;
        return os;
    }

   protected:
    int weight;
};

class Box : public Object {
   public:
    Box(int height, int width, int weight) : Object(weight), height(height), width(width) {
        cout << "Box construct" << endl;
    }
    ~Box() {
        cout << "Box destruct" << endl;
    }
    void setSize(int h, int w) {
        height = h;
        width = w;
    }

    friend ostream& operator<<(ostream& os, const Box& b) {
        os << "Box weight " << b.weight << endl
           << "Height: " << b.height << endl
           << "Width: " << b.width << endl;
        return os;
    }

   private:
    int height, width;
};

int main(int argc, char* argv[]) {
    Box myBox(10, 20, 1);

    cout << myBox;

    return 0;
}

//OUTPUT:
/*

Object construct
Box construct
Box weight 1
Height: 10
Width: 20
Box destruct
Object destruct

*/
/*
可以看到类的初始化是类似于栈的增长方式
*/