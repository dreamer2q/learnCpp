
#include <bits/stdc++.h>

using namespace std;

//A^B 快速幂

int quickExpWith3Digits(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    auto r = quickExpWith3Digits(a, b >> 1) % 1000;
    r = r * r % 1000;
    if (b % 2) {
        r = r * a % 1000;
    }
    return r;
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;

        cout << quickExpWith3Digits(a, b) << endl;
    }
    return 0;
}