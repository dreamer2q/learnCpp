#include <bits/stdc++.h>

using namespace std;

int main() {
    int cas;
    cin >> cas;
    while (cas--) {
        int n, m;
        cin >> n >> m;
        vector<int> sig(n + 1, 0);
        sig[0] = -1;  //必败点
        for (int i = 1; i <= n; i++) {
            bool win = false;
            for (int j = max(i - m, 0); j < i; j++) {
                if (sig[j] == -1) {
                    win = true;
                    break;
                }
            }
            sig[i] = win ? 1 : -1;
        }
        cout << (sig[n] == 1 ? "first" : "second") << endl;
    }
    return 0;
}