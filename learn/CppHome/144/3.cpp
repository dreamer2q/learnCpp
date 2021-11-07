
/*
构造函数和析构函数有什么作用？

这个两个函数都是Class专有的函数，构造函数用来初始化一个类，创建类的时候执行，可以进行重载；
析构函数用来释放一个类申请的资源，在类被销毁时候执行。

这两个函数都可以不写，但是编译器会帮我们默认生产。

如果有类的嵌套，则执行循序类似于一个Stack模型。

当然如果涉及到类的继承，可能里面有很多细节需要注意，这里不进行展开。
*/

#include <iostream>
#include <string>

using namespace std;

class Person {
   public:
    Person() = delete;  //这是的构造函数
    Person(int age, string name) : age(age), name(name) {
        cout << "执行Person，构造函数" << endl;
    }
    ~Person() {
        cout << "这些Person, 析构函数" << endl;
    };  // 这是析构函数

    void Descript() {
        cout << "执行Person.Descript" << endl;
        cout << "Name:" << name << endl
             << "Age:" << age << endl;
    }

   protected:
    int age;
    string name;
};

class Teacher : Person {
   public:
    Teacher() = delete;
    Teacher(int age, string name, string teaching) : Person(age, name), field(teaching) {
        cout << "执行Teacher构造函数" << endl;
    }
    ~Teacher() {
        cout << "执行Teacher析构函数" << endl;
    }
    void Descript() {
        cout << "执行Teacher.Descript" << endl;
        Person::Descript();
        cout << "Teaching:" << field << endl;
    }

   private:
    string field;
};

int main() {
    Teacher Li(20, "Jack Li", "Computer Science");
    Li.Descript();
    return 0;
}
