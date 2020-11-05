
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    while (cin >> t, t > 0) {
        vector<int> facilities;
        int sum = 0;
        for (int i = 0; i < t; i++) {
            int v, n;
            cin >> v >> n;
            sum += v * n;
            for (int j = 0; j < n; j++) {
                facilities.push_back(v);
            }
        }
        int v = sum / 2;
        vector<int> dp(v + 1, 0);
        for (int i = 0; i < facilities.size(); i++) {
            for (int j = v; j >= facilities[i]; j--) {
                dp[j] = max(dp[j], dp[j - facilities[i]] + facilities[i]);
            }
        }
        cout << sum - dp[v] << " " << dp[v] << endl;
    }
    return 0;
}