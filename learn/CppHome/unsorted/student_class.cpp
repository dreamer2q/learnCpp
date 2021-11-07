#include <memory.h>
#include <string.h>

#include <iostream>

using namespace std;

class Student {
   public:
    Student() = delete;

    Student(int ag, int num, const char *nm) : age(ag), number(num) {
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
    };

    Student(const Student &st) : age(st.age), number(st.number) {
        name = new char[strlen(st.name) + 1];
        strcpy(name, st.name);
    }

    ~Student() {
        delete name;
    };

    void display() {
        cout << "Student: " << name << endl
             << "Number: " << number << endl
             << "Age: " << age << endl;
    };

   private:
    int age;
    int number;
    char *name;
};

int main() {
    Student Li(10, 2, "sh1");
    Student Li2(Li);

    Li.display();
    Li2.display();

    Student stu();  //这里是一个函数声明，卧槽。？？？？不会报错？？？？？

    Student st(11, 22, "caosndjfalksdjf");
    st.display();

    return 0;
}