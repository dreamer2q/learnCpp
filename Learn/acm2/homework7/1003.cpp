
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int cost, n;
        cin >> cost >> n;
        vector<pair<int, int>> mi;
        for (int i = 0; i < n; i++) {
            int c, v, k;
            cin >> c >> v >> k;
            for (int j = 0; j < k; j++) {
                mi.push_back(make_pair(c, v));
            }
        }
        vector<int> dp(cost + 1, 0);
        for (int i = 0; i < mi.size(); i++) {
            for (int j = cost; j >= mi[i].first; j--) {
                dp[j] = max(dp[j], dp[j - mi[i].first] + mi[i].second);
            }
        }
        cout << dp[cost] << endl;
    }
    return 0;
}
