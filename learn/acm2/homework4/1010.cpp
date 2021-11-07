#include <bits/stdc++.h>

using namespace std;

// 卡特兰数

// strange

long long dp[40][40];

void init() {
    for (int i = 1; i <= 35; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
}

int main() {
    init();
    int no = 0;
    int n;
    while (cin >> n && n != -1) {
        cout << ++no << " " << n << " " << 2 * dp[n][n] << endl;
    }

    return 0;
}
