#include <bits/stdc++.h>

using namespace std;

const int nmax = 31231;
int h[nmax], v[nmax];

int _hash(int key) {
    int t = key % nmax;
    if (t < 0) t += nmax;
    while (h[t] != 0 && v[t] != key) {
        t = (t + 1) % nmax;
    }
    return t;
}

int main() {
    int n;
    while (cin >> n) {
        memset(h, 0, sizeof(h));
        memset(v, 0, sizeof(v));
        int ans = 0;
        while (n--) {
            int tmp;
            scanf("%d", &tmp);
            int p = _hash(tmp);
            h[p]++;
            v[p] = tmp;
            if (h[p] > ans)
                ans = h[p];
        }
        std::cout << ans << endl;
    }

    return 0;
}