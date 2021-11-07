#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<pair<int, int>> k;
        for (int i = 0; i < n; i++) {
            int v, c;
            cin >> v >> c;
            k.push_back(make_pair(v, c));
        }
        int calories;
        cin >> calories;
        vector<int> dp(calories + 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j = k[i].second; j <= calories; j++) {
                dp[j] = max(dp[j], dp[j - k[i].second] + k[i].first);
            }
        }
        cout << dp[calories] << endl;
    }
    return 0;
}
