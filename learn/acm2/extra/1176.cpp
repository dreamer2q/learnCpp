#include <bits/stdc++.h>

using namespace std;

int dp[100100][11];

int main() {
    int n;
    while (cin >> n, n) {
        int x, t, T = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x, &t);
            dp[t][x]++;
            if (T < t) T = t;
        }
        //dp
        for (int i = T - 1; i >= 0; i--) {
            dp[i][0] += max(dp[i + 1][0], dp[i + 1][1]);
            for (int j = 1; j < 10; j++) {
                dp[i][j] += max(dp[i + 1][j - 1], max(dp[i + 1][j], dp[i + 1][j + 1]));
            }
            dp[i][10] += max(dp[i + 1][9], dp[i + 1][10]);
        }
        cout << dp[0][5] << endl;
        memset(dp, 0, sizeof(dp));
    }
    return 0;
}
