#include <bits/stdc++.h>
using namespace std;

int dp[10000];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> value;
        vector<int> cost;
        for (int i = 0; i < m; i++) {
            int c, v, count;
            int b = 1;
            cin >> c >> v >> count;
            while (count >= b) {
                cost.push_back(c * b);
                value.push_back(v * b);
                count -= b;
                b <<= 1;
            }
            if (count) {
                cost.push_back(count * c);
                value.push_back(count * v);
            }
        }
        for (int i = 0; i < cost.size(); i++) {
            for (int j = n; j >= cost[i]; j--) {  //多重背包转换成01背包
                dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
            }
        }
        int ans = dp[0];
        for (int i = 1; i <= n; i++) {
            if (dp[i] > ans) ans = dp[i];
        }
        cout << ans << endl;
        memset(dp, 0, sizeof(dp));
    }
    return 0;
}