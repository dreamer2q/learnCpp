#include <bits/stdc++.h>
using namespace std;

int dp[1100];

int main() {
    int m, n;
    while (cin >> m >> n) {
        if (m == -1 && n == -1) break;
        vector<int> value;
        vector<int> cost;
        for (int i = 0; i < n; i++) {
            int v, c;
            scanf("%d %d", &v, &c);
            value.push_back(v);
            cost.push_back(c);
        }

        // memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= m; i++) {
            dp[i] = -1000000;
        }
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= cost[i]; j--) {
                dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
            }
        }

        if (dp[m] >= 0) {
            cout << dp[m] << endl;
        } else {
            cout << -1 << endl;
        }
    }

    return 0;
}