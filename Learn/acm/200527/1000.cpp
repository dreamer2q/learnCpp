#include <bits/stdc++.h>

using namespace std;

int main() {
    map<int, int> m;
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            m[tmp]++;
        }
        int ans = 0;
        for (const auto& e : m) {
            if (e.second >= ((n + 1) / 2)) {
                cout << e.first << endl;
                break;
            }
        }
        m.clear();
    }

    return 0;
}