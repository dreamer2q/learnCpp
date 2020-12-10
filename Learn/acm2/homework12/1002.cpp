#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> sig(n + 1, 0);
        sig[0] = -1;  //必败点
        for (int i = 1; i <= n; i++) {
            bool win = false;
            for (int j = 1; i - j >= 0; j *= 2) {
                if (sig[i - j] == -1) {
                    win = true;
                    break;
                }
            }
            sig[i] = win ? 1 : -1;
        }
        cout << (sig[n] == 1 ? "Kiki" : "Cici") << endl;
    }
    return 0;
}
