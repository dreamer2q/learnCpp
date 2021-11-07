
#include <bits/stdc++.h>

using namespace std;

long long dp[51] = {0, 3, 6, 6};

void init() {
    for (int i = 4; i <= 50; i++) {
        dp[i] = dp[i - 1] + 2 * dp[i - 2];
    }
}

int main() {
    init();

    int n;
    while (cin >> n) {
        cout << dp[n] << endl;
    }

    return 0;
}