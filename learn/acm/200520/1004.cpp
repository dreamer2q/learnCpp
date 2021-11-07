#include <bits/stdc++.h>

using namespace std;

#define NMAX 5000

int c1[NMAX];
int c2[NMAX];

int delta[] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289};

int main() {
    for (int i = 0; i <= 300; i++) {
        c1[i] = 1;
        c2[i] = 0;
    }
    for (int i = 1; i < 17; i++) {
        for (int j = 0; j <= 300; j++) {
            for (int k = 0; k + j <= 300; k += delta[i]) {
                c2[k + j] += c1[j];
            }
        }
        for (int j = 0; j <= 300; j++) {
            c1[j] = c2[j];
            c2[j] = 0;
        }
    }
    int n;
    while (cin >> n) {
        if (n == 0) break;
        cout << c1[n] << endl;
    }
    return 0;
}