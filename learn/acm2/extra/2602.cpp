#include <bits/stdc++.h>

using namespace std;

int dp[1100];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, v;
        cin >> n >> v;
        vector<int> value;
        vector<int> cost;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            value.push_back(v);
        }
        for (int i = 0; i < n; i++) {
            int c;
            cin >> c;
            cost.push_back(c);
        }
        for (int i = 0; i < n; i++) {
            for (int j = v; j >= cost[i]; j--) {  //01背包，从后向前
                dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
            }
        }
        cout << dp[v] << endl;
        memset(dp, 0, sizeof(dp));
    }
    return 0;
}