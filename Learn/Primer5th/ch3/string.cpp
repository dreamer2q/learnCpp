#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    int a[10][10] = {};

    int i = 0;
    for (auto& row : a) {
        for (auto& e : row) {
            e = i++;
        }
    }

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int(*t)[10] = begin(a); t != end(a); t++) {
        for (int* c = begin(*t); c != end(*t); c++) {
            cout << *c << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int(*t)[10] = a; t != a + 10; t++) {
        for (int* c = *t; c != *t + 10; c++) {
            cout << *c << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}