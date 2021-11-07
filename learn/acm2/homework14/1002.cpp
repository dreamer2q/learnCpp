#include <bits/stdc++.h>

using namespace std;

#define NMAX 101000

int c1[NMAX];
int c2[NMAX];

int main() {
    int n1, n2, n5;

    while (cin >> n1 >> n2 >> n5) {
        if (n1 == 0 && n2 == 0 && n5 == 0) break;

        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));

        //for num_1
        for (int i = 0; i <= n1; i++) {
            c1[i] = 1;
        }

        //for num_2
        for (int j = 0; j <= n1; j++) {
            for (int k = 0; k + j <= n1 + 2 * n2; k += 2) {
                c2[j + k] += c1[j];
            }
        }

        for (int i = 0; i <= n1 + 2 * n2; i++) {
            c1[i] = c2[i];
            c2[i] = 0;
        }

        //for num_5
        for (int j = 0; j <= n1 + 2 * n2; j++) {
            for (int k = 0; k + j <= n1 + 2 * n2 + 5 * n5; k += 5) {
                c2[j + k] += c1[j];
            }
        }

        for (int i = 0; i <= NMAX; i++) {
            if (!c2[i]) {
                cout << i << endl;
                break;
            }
        }
    }

    return 0;
}