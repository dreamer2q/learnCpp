
#include <bits/stdc++.h>

using namespace std;

const int infinite = 10000000;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int empty, full, delta;
        cin >> empty >> full;
        delta = full - empty;
        int n;
        cin >> n;
        vector<pair<int, int>> coins;
        for (int i = 0; i < n; i++) {
            int value, weight;
            cin >> value >> weight;
            coins.push_back(make_pair(value, weight));
        }
        vector<int> dp(delta + 1, infinite);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = coins[i].second; j <= delta; j++) {
                dp[j] = min(dp[j], dp[j - coins[i].second] + coins[i].first);
            }
        }
        if (dp[delta] == infinite) {
            cout << "This is impossible." << endl;
        } else {
            cout << "The minimum amount of money in the piggy-bank is " << dp[delta] << "." << endl;
        }
    }
    return 0;
}