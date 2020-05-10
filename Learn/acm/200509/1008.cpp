#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace std;

int k, S[101];
int stat[10001];

int sg(int n) {
    bool g[101] = {false};
    for (int i = 0; i < k; i++) {
        int t = n - S[i];
        if (t < 0) break;
        if (stat[t] == -1) {
            stat[t] = sg(t);
        }
        g[stat[t]] = true;
    }
    for (int i = 0;; i++) {
        if (g[i] == false)
            return i;
    }
}

int main() {
    //ifstream cin("test.txt");

    while (cin >> k) {
        if (k == 0) break;
        for (int i = 0; i < k; i++)
            cin >> S[i];
        memset(stat, -1, sizeof(stat));
        sort(S, S + k);
        int n;
        cin >> n;
        while (n--) {
            int t, ans = 0;
            cin >> t;
            while (t--) {
                int tmp;
                cin >> tmp;
                ans ^= sg(tmp);
            }
            cout << (ans ? "W" : "L");
        }
        cout << endl;
    }
    return 0;
}