#include <bits/stdc++.h>

using namespace std;

#define NMAX 200

int c1[NMAX];
int c2[NMAX];

int main() {
    int n;

    while (cin >> n) {
        for (int i = 0; i <= n; i++) {
            c1[i] = 1;
            c2[i] = 0;
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k + j <= n; k += i) {
                    c2[j + k] += c1[j];
                }
            }
            for (int j = 0; j <= n; j++) {
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }

        cout << c1[n] << endl;
    }
    return 0;
}