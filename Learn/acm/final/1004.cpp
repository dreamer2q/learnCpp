/*
 * File Created: Wednesday, 24th June 2020 7:48:15 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 24th June 2020 8:04:20 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<int> vn;
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            vn.push_back(tmp);
        }
        for (int i = 0; i < m; i++) {
            int left, right;
            cin >> left >> right;
            int l = min(left, right);
            int r = max(left, right);
            long long ans = 0;
            for (int j = l - 1; j < r; j++) {
                ans += vn[j];
            }
            cout << ans << endl;
        }
    }

    return 0;
}