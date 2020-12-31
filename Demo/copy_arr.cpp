#include <bits/stdc++.h>

using namespace std;

struct Arr {
    int a[10];
};

int main() {
    Arr arr = {1, 2, 3, 4, 5, 6, 7, 8};
    Arr b;
    b = arr;

    for (int i = 0; i < 10; i++) {
        cout << b.a[i] << endl;
    }

    return 0;
}