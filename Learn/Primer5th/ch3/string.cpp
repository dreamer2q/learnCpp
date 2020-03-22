#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    string s1 = "this is a string";
    string s2 = s1;
    string s3;
    string s4(10, 'c');

    size_t l1 = s1.size();
    cout << l1 << endl;

    while (std::getline(cin, s3)) {
        cout << s3;
    }
    cout << "over" << endl;

    return 0;
}