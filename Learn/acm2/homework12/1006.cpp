#include <bits/stdc++.h>

using namespace std;

vector<int> proc(int n, int m) {
    vector<int> ret;
    int sg[2222] = {0};
    sg[0] = -1;
    for (int i = 1; i <= n; i++) {
        bool flag = false;
        for (int j = max(0, i - m); j < i; j++) {
            if (sg[j] == -1) {
                flag = true;
                break;
            }
        }
        sg[i] = flag ? 1 : -1;
    }
    for (int i = 1; i <= m; i++) {
        if (i > n || sg[n - i] == -1) ret.push_back(i);
    }
    return ret;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        auto ret = proc(n, m);
        if (ret.empty()) {
            cout << "none";
        } else {
            for (int i = 0; i < ret.size(); i++) {
                cout << ret[i];
                if (i != ret.size() - 1) cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
