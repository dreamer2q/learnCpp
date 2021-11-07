#include <cstring>
#include <iostream>
using namespace std;

int f[1001];

int sg(int n) {
    bool g[1001] = {false};
    for (int i = 1; i <= 1000; i++) {
        int t = n - i;
        if (t < 0) break;
        if (f[t] == -1)
            f[t] = sg(t);
        g[f[t]] = true;
    }
    for (int i = 0;; i++) {
        if (!g[i])
            return i;
    }
}

int main() {
    memset(f, -1, sizeof(f));
    int n;
    while (cin >> n) {
        if (n == 0) break;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            ans ^= sg(t);
        }
        cout << (ans ? "Rabbit Win!" : "Grass Win!") << endl;
    }
    return 0;
}