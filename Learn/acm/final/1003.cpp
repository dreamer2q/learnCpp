/*
 * File Created: Wednesday, 24th June 2020 6:41:08 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 24th June 2020 7:46:31 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

int dp[100010][2];

int main() {
    int n;
    while (cin >> n) {
        vector<int> vn;
        vn.push_back(0);
        for (int i = 1; i <= n; i++) {
            int tmp;
            cin >> tmp;
            vn.push_back(tmp);
        }
        dp[1][1] = vn[1];
        // dp[2][0] = vn[1];
        // dp[2][1] = vn[2];
        for (int i = 2; i <= n; i++) {
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + vn[i]);
        }
        cout << max(dp[n][1], dp[n][0]) << endl;
        memset(dp, 0, sizeof(dp));
    }
    return 0;
}