
#include <bits/stdc++.h>

using namespace std;

long long dp[54] = {0, 1, 2};

void init() {
    for (int i = 3; i < 54; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
}

int main() {
    init();

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int dx = b - a;
        cout << dp[dx] << endl;
    }

    return 0;
}