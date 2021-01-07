#include <bits/stdc++.h>

using namespace std;

int dp[25][15];

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<vector<int>> data;
        for (int i = 0; i < n; i++) {
            vector<int> line;
            for (int j = 0; j < k; j++) {
                int t;
                scanf("%d", &t);
                line.push_back(t);
            }
            data.push_back(line);
        }
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < k; i++) {
            dp[0][i] = 0;
        }
        for (int t = 1; t < n; t++) {
            for (int j = 0; j < k; j++) {
                for (int i = 0; i < k; i++) {
                    dp[t][j] = min(dp[t][j], dp[t - 1][i] + abs(data[t][j] - data[t - 1][i]));
                }
            }
        }
        int ans = 10000000;
        for (int i = 0; i < k; i++) {
            if (ans > dp[n - 1][i]) ans = dp[n - 1][i];
        }
        cout << ans << endl;
    }
    return 0;
}