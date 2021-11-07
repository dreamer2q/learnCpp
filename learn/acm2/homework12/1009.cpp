#include <bits/stdc++.h>

using namespace std;

int f[11001];
int sg(vector<int>& steps, int n) {
    int g[101] = {false};
    for (int i = 0; i < steps.size(); i++) {
        int t = n - steps[i];
        if (t < 0) break;
        if (f[t] == -1)
            f[t] = sg(steps, t);
        g[f[t]] = true;
    }
    for (int i = 0;; i++)
        if (!g[i]) return i;
}

int main() {
    // ifstream inf("1009.txt");
    // cin.rdbuf(inf.rdbuf());  //redirect cin to file, in order to test

    int cas;
    while (cin >> cas, cas) {
        vector<int> steps;
        for (int i = 0; i < cas; i++) {
            int tmp;
            cin >> tmp;
            steps.push_back(tmp);
        }
        sort(steps.begin(), steps.end());
        memset(f, -1, sizeof(f));
        int n;
        cin >> n;
        while (n--) {
            int t, ans = 0;
            cin >> t;
            for (int i = 0; i < t; i++) {
                int tmp;
                cin >> tmp;
                ans ^= sg(steps, tmp);
            }
            cout << (ans == 0 ? "L" : "W");
        }
        cout << endl;
    }
    return 0;
}
