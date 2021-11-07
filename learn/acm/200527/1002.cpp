#include <bits/stdc++.h>

using namespace std;

const int nmax = 1000010;
const int offset = 500000;

int mset[nmax];

int main() {
    int n, m;
    while (cin >> n >> m) {
        memset(mset, 0, sizeof(nmax));
        for (int i = 0; i < n; i++) {
            int t;
            scanf("%d", &t);
            if (t < m) continue;
            mset[t + offset] = 1;
        }
        for (int i = nmax - 1; i >= 0; i--) {
            if (mset[i]) {
                printf("%d", i - offset);
                m--;
                if (m == 0) break;
                putchar(' ');
            }
        }
        putchar(10);
    }

    return 0;
}