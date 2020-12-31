#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> c1(n + 1, 1);
        vector<int> c2(n + 1, 0);

        for (int i = 2; i <= n; i++) {  //循环x^1 ... x^n
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k + j <= n; k += i) {
                    c2[j + k] += c1[j];
                }
            }
            c1 = c2;
            c2.assign(n + 1, 0);
        }
        cout << c1[n] << endl;
    }
    return 0;
}
