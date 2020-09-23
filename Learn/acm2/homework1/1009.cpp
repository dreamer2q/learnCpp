#include <bits/stdc++.h>

using namespace std;

int sum_to(int n) {
    return n * (n + 1) / 2;
}

int main() {
    int n;
    while (cin >> n) {
        cout << sum_to(n) << endl
             << endl;
    }

    return 0;
}