#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n, n) {
        vector<int> m(n, 0);
        int ans = 0, an = 0;
        for (int i = 0; i < n; i++) {
            cin >> m[i];
            ans ^= m[i];
        }
        if (ans != 0) {
            for (int i = 0; i < n; i++) {
                an += m[i] > (ans ^ m[i]);
            }
        }
        cout << an << endl;
    }
    return 0;
}

