#include <iostream>

using namespace std;

int main() {
    int i = 0;
    while (new int[1 << 10]) {
        i++;
    }
    cout << i << endl;
}