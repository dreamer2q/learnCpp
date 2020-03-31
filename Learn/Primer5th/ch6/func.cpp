#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_msg(initializer_list<string> lst) {
    for (auto beg = lst.begin(); beg != lst.end(); beg++) {
        cout << *beg << endl;
    }
}

int gArr[10];

//using alias
using rArr = int[10];
rArr* func3(int i) {
    return &gArr;
}

//conventional writing style
int (*func2(int i))[10] {
    return &gArr;
}

//trailing return type
auto func(int i) -> int (*)[10] {
    return &gArr;
};

int main() {
    print_msg({"message1", "this is a message two"});

    (*func(0))[0] = 1;

    return 0;
}