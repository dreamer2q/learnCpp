/*
2020年4月30日
by dreamer2q
*/

#include <iostream>

using namespace std;

struct Base1 {
    int x;
};

struct Base2 {
    float y;
};

struct Derived : Base1, Base2 {};

/*
不可用进行转换，为什么呢？
因为Derived的继承顺序是先Base1, 后 Base2
而指针只是指向Derived的开始位置
对于不同位置的元素，我们需要计算与和起始位置的偏移量
这样我们才能正确的访问相应的元素

说到底，就是理解继承的不同类型在内存的排布方式
很显然，和我们继承的顺序是一样的。
*/

int main() {
    Derived *pd = new Derived;

    pd->x = 1;
    pd->y = 2.0f;

    void *pv = pd;
    Base2 *pb = static_cast<Base2 *>(pv);
    Base1 *pb1 = static_cast<Base1 *>(pv);

    cout << pd->x << " " << pd->y << endl;

    cout << pb->y << endl;
    cout << pb1->x << endl;

    delete pd;
    return 0;
}

//OUTPUT:
/*
1 2
1.4013e-45
1
*/
