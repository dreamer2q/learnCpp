#include <iostream>

using namespace std;

int* fnl() {
    //int* p = new int(5);
    return new int(5);
}

int main() {
    auto a = fnl();

    cout << "a is " << a << endl;
    cout << "*a is " << *a << endl;

    delete a;

    return 0;
}
