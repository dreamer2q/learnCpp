#include <bits/stdc++.h>

using namespace std;

const int nmax = 50021;

int main() {
    int x[101];
    for (int i = 1; i <= 100; i++) {
        x[i] = i * i;
    }

    int a, b, c, d;
    unordered_map<int, int> m;
    while (cin >> a >> b >> c >> d) {
        if (a > 0 && b > 0 && c > 0 && d > 0 || a < 0 && b < 0 && c < 0 && d < 0) {
            cout << 0 << endl;
            continue;
        }
        for (int x1 = 1; x1 <= 100; x1++) {
            for (int x2 = 1; x2 <= 100; x2++) {
                int t = a * x[x1] + b * x[x2];
                m[t]++;
            }
        }
        int ans = 0;
        for (int x1 = 1; x1 <= 100; x1++) {
            for (int x2 = 1; x2 <= 100; x2++) {
                int t = -(c * x[x1] + d * x[x2]);
                ans += m[t];
            }
        }
        cout << ans * 16 << endl;
        m.clear();
    }

    return 0;
}