#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        n %= 8;
        if (n == 2 || n == 6) {
            cout << "yes";
        } else {
            cout << "no";
        }
        cout << endl;
    }

    return 0;
}