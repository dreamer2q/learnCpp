

#include <bits/stdc++.h>

using namespace std;

long long dp[51] = {0, 1, 2};

void init() {
    for (int i = 3; i <= 50; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
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
