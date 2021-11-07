
#include <bits/stdc++.h>

using namespace std;

int expLastDigit(int n) {
    if (n == 0) return 0;
    int r = 1;
    for (int i = n; i > 0; i--) {
        r *= n;
        r %= 10;
    }
    return r;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << expLastDigit(n % 100) << endl;
    }
    return 0;
}