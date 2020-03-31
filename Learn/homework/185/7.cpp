

/**
 *  
 *  class 的静态方法
 *  2020年3月31日
 *  by dreamer2q
 * 
 */

#include <iostream>

using namespace std;

class Cat {
   public:
    Cat() {
        _cat_num++;
        cout << "new a cat" << endl;
    }
    Cat(const string name) : Cat() { m_name = name; };
    ~Cat() {
        _cat_num--;
        cout << "delete a cat" << endl;
    }

    //这里一般使用友元函数
    friend ostream& operator<<(ostream& out, const Cat& cat) {
        out << "here comes a cat: " << cat.name() << endl;
        return out;
    }
    const string name() const { return m_name.empty() ? "I got no name" : m_name; }

    //这里是静态成员函数，使用Cat::getNumOfCats() 调用
    //也可以使用成员方法访问。
    static int getNumOfCats() { return _cat_num; }

   private:
    //这里仅仅是声明，没有实际定义这个函数，如果不在外部定义，链接额时候出现，undefined reference错误!!
    static int _cat_num;
    string m_name;
};

//由于在class里面的static变量只是简单的声明，没有实际的定义，所以这里面定义真正的class static变量，其实就是给变量分配空间啦
//到这里就可以理解为什么类内静态变量只有一个实例
int Cat::_cat_num = 0;

int main() {
    cout << "start: " << Cat::getNumOfCats() << endl;
    Cat cat1("SmallRed"), cat2;

    cout << cat1;
    cout << cat2;

    cout << "after: " << Cat::getNumOfCats() << endl;

    return 0;
}