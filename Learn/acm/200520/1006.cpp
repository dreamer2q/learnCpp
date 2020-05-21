#include <bits/stdc++.h>

using namespace std;

#define NMAX 10000

int c1[NMAX];
int c2[NMAX];

int main() {
    int cas;
    cin >> cas;
    while (cas--) {
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        for (int i = 1; i <= 26; i++) {
            int n;
            cin >> n;
            if (i == 1) {
                for (int j = 0; j <= n; j++) {
                    c1[j] = 1;
                }
            } else {
                for (int j = 0; j <= 50; j++) {
                    for (int k = 0; k + j <= 50 && k <= i * n; k += i) {
                        c2[k + j] += c1[j];
                    }
                }
                memcpy(c1, c2, sizeof(c2));
                memset(c2, 0, sizeof(c2));
            }
        }
        int sum = 0;
        for (int i = 1; i <= 50; i++) {
            sum += c1[i];
        }
        cout << sum << endl;
    }
    return 0;
}