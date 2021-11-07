#include <cstring>
#include <iostream>
using namespace std;

int fib(int n) {
    if (n == 1 || n == 2)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int fb[] = {
    1,
    1,
    2,
    3,
    5,
    8,
    13,
    21,
    34,
    55,
    89,
    144,
    233,
    377,
    610,
    987,
    1597,
};

int f[10001];

int sg(int n) {
    bool g[101] = {false};
    for (int i = 1; i < sizeof(fb) / sizeof(fb[0]); i++) {
        int t = n - fb[i];
        if (t < 0) break;
        if (f[t] == -1)
            f[t] = sg(t);
        g[f[t]] = true;
    }
    for (int i = 0;; i++) {
        if (g[i] == false) {
            return i;
        }
    }
}

int main() {
    memset(f, -1, sizeof(f));
    int m, n, p;
    while (cin >> m >> n >> p) {
        if (m == 0 && n == 0 && p == 0) break;
        cout << ((sg(m) ^ sg(n) ^ sg(p)) == 0 ? "Nacci" : "Fibo") << endl;
    }
    return 0;
}
