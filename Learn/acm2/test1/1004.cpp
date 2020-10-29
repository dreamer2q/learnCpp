#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    int c = a % b;
    while (c) {
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}

void test_gcd() {
    cout << gcd(1, 2) << endl;
    cout << gcd(2, 6) << endl;
    cout << gcd(6, 12) << endl;
    cout << gcd(2, 21) << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int g = gcd(a * c, b * d);
        cout << a * c / g << " " << b * d / g << endl;
    }

    return 0;
}