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
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < k; i++) {
            int credit, number;
            cin >> credit >> number;
            if (i == 0) {
                for (int z = 0; z <= number; z++) {
                    c1[z * credit] = 1;
                }
                continue;
            }
            for (int k = 0; k <= n; k++) {
                for (int z = 0; z <= number; z++) {
                    c2[k + z * credit] += c1[k];
                }
            }
            memcpy(c1, c2, sizeof(c1));
            memset(c2, 0, sizeof(c2));
        }
        cout << c1[n] << endl;
    }

    return 0;
}