
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    vector<int> goods = {150, 200, 350};
    while (t--) {
        int n;
        cin >> n;
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < goods.size(); i++) {
            for (int j = goods[i]; j <= n; j++) {
                dp[j] = max(dp[j], dp[j - goods[i]] + goods[i]);
            }
        }
        cout << n - dp[n] << endl;
    }
    return 0;
}