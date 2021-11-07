
#include <bits/stdc++.h>

using namespace std;

int main() {
    long long dp[22] = {3, 7};
    for (int i = 2; i <= 20; i++) {
        dp[i] = 2 * dp[i - 1] + dp[i - 2];
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << dp[n - 1] << endl;
    }

    return 0;
}
