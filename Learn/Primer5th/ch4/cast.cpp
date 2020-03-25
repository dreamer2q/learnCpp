
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    const char* text = "hello, this is a test string.......terminated with null";
    cout << text << endl;

    char* p = const_cast<char*>(text);  //use const_cast to cast away const attribute

    //! Undefined
    p[0] = '1';
    cout << text << endl;
    //terminated without any sign

    //code below won't be executed
    cerr << "test" << endl;

    return 0;
}
