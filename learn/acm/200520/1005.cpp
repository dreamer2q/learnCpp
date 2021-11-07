#include <bits/stdc++.h>

using namespace std;

#define NMAX 10000

int c1[NMAX];
int c2[NMAX];

int main() {
    int n;
    while (cin >> n, n) {
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int p, m;
            cin >> p >> m;
            sum += p * m;
            if (i == 0) {
                for (int j = 0; j <= m; j++) {
                    c1[j * p] = 1;
                }
            } else {
                for (int j = 0; j <= sum; j++) {
                    for (int k = 0; k + j <= sum && k <= p * m; k += p) {
                        c2[k + j] += c1[j];
                        if (c2[k + j] > 10000) {
                            c2[k + j] %= 10000;
                        }
                    }
                }
                memcpy(c1, c2, sizeof(c1));
                memset(c2, 0, sizeof(c2));
            }
        }
        if (sum % 3 || !c1[sum / 3]) {
            cout << "sorry" << endl;
        } else {
            cout << c1[sum / 3] << endl;
        }
    }

    return 0;
}