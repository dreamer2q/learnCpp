/*

复制构造函数，又称拷贝构造函数（Copy Constructor)
Copy Constructor 是一个特殊的构造函数，一般只有一个参数，这个参数一般是用const修饰的，对自己类的一个引用(reference)。

# 什么时候会用到Copy Constructor?

当我们定义一个对象时，它是由另外一个对象来初始化的时候就用到Copy Constructor了。还有就是在一个方法以值作为参数传进去或者一个方法中以值作为返回。

如果一个类缺少了Copy Constructor，编译器会默认生产一个。
当然，我们也可以通过一些方法来禁用Copy Constructor
*/
/*
此外，我们还有赋值运算符，通过在类内重载=运算符，我们就可以实现给一个类的赋值操作。
但是注意，在定义的使用使用=，并不是使用赋值操作，而是使用Copy Constructor
*/

#include <iostream>
#include <string>

using namespace std;

class Person {
   public:
    Person() = delete;  //这是的构造函数
    //Person(const Person& p) = default;  //让编译器默认生产一个复制构造函数，当然这个语句也可以不写。
    Person(const Person& p) : age(p.age), name(p.name) {
        cout << "Person Copy Constructor" << endl;
    }
    Person(int age, string name) : age(age), name(name) {
        cout << "执行Person，构造函数" << endl;
    }
    ~Person() {
        cout << "这些Person, 析构函数" << endl;
    };  // 这是析构函数

    Person& operator=(const Person& p) {
        cout << "Person Assignment Operator" << endl;
        this->age = p.age;
        this->name = p.name;
        return *this;
    }

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
    Teacher(const Teacher& t) : field(t.field), Person(t) {
        cout << "Teacher Copy Constructor" << endl;
    }
    Teacher& operator=(const Teacher& t) {
        this->age = t.age;
        this->name = t.name;
        this->field = t.field;
        cout << "Teacher Assignment Operator" << endl;
        return *this;
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
    Teacher Yang(21, "Mr Yang", "English");
    Teacher Li2 = Li;  //这里由于是赋值初始化，调用Copy Constructor
    Teacher Li3(Li);   //这里显式调用，Copy Constructor
    Li.Descript();
    Yang.Descript();

    Yang = Li;  //调用 Assigment Operator
    Yang.Descript();
    return 0;
}
