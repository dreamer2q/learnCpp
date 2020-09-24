
#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    int m = a % b;
    while (m) {
        a = b;
        b = m;
        m = a % b;
    }
    return b;
}

void test() {
    gcd(1, 3);
    gcd(12, 4);
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        cout << a * b / gcd(a, b) << endl;
    }

    return 0;
}