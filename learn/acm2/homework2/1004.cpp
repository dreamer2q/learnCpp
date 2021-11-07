#include <bits/stdc++.h>

using namespace std;
int A, B, n;

int cache[1000];
int f(int n) {
    if (cache[n] != -1) return cache[n];
    if (n == 1 || n == 2) return cache[n] = 1;
    int r = A * f(n - 1) + B * f(n - 2);
    return cache[n] = r % 7;
}

/*
正确的算法过不了
抱歉
*/

int main() {
    while (cin >> A >> B >> n) {
        if (A == 0 || B == 0 || n == 0) break;
        memset(cache, -1, sizeof(cache));
        if (n <= 100) {
            cout << f(n) << endl;
        } else {
            vector<int> m;
            for (int i = 1; i <= 100; i++) {
                m.push_back(f(i));
            }
            int l;
            auto ret = search(m.begin() + 4, m.end(), m.begin() + 2, m.begin() + 4);
            if (ret != m.end()) {
                l = ret - m.begin() - 2;
            }
            cout << f((n - 2) % l + 2) << endl;
        }
    }

    return 0;
}