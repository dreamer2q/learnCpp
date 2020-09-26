
/*
* 类内运算符重载
* by dreamer2q
* 2020年5月12日
*/

#include <iostream>

using namespace std;

class Counter {
public:
    Counter(int t) : count(t) {}

    //对+进行重载
    Counter operator+(const Counter& t) {
        return Counter(count + t.count);
    }

    //友元函数，重载输出
    friend ostream& operator<<(ostream& os, const Counter& c) {
        os << c.count << endl;
        return os;
    }

private:
    int count;
};

int main() {
    Counter c1(1), c2(2);

    cout << c1 + c2;
    cout << c1 + 10;
    return 0;
}

//output:
/*
3
11
*/