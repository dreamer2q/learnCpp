

#include <bits/stdc++.h>

using namespace std;

long long dp[55] = {0, 1, 3};

void init() {
    for (int i = 3; i < 32; i++) {
        dp[i] = dp[i - 1] + 2 * dp[i - 2];
    }
}

int main() {
    init();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << dp[n] << endl;
    }

    return 0;
}
