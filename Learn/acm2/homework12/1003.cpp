#include <bits/stdc++.h>

using namespace std;

int fib[] = {1,
             1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597};

int f[10001] = {-1};

int sg(int x) {
    bool g[101] = {false};
    for (int i = 1; i < sizeof(fib) / sizeof(fib[0]); i++) {
        int t = x - fib[i];  //获取下一个状态
        if (t < 0) break;    //状态是否合法
        if (f[t] == -1) {    //没有记忆
            f[t] = sg(t);    // 获取子节点的sg值, 记忆化递归
        }
        g[f[t]] = true;
    }
    for (int i = 0;; i++)
        if (!g[i]) return i;
}

int main() {
    // memset(f, -1, sizeof(f));
    int m, n, p;
    while (cin >> m >> n >> p) {
        if (!m && !n && !p) break;
        auto result = sg(m) ^ sg(n) ^ sg(p);
        cout << (result == 0 ? "Nacci" : "Fibo") << endl;
    }
    return 0;
}
