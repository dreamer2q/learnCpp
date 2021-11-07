
#include <bits/stdc++.h>

using namespace std;

long long dp[55] = {1, 2, 3, 4};

void init() {
    for (int i = 4; i < 50; i++) {
        dp[i] = dp[i - 1] + dp[i - 3];
    }
}

int main() {
    init();
    int n;
    while (cin >> n) {
        if (n == 0) break;
        cout << dp[n - 1] << endl;
    }

    return 0;
}