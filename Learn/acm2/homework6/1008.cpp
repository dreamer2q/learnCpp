#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;  //经验值
    int m;  //忍耐度
    int k;  //怪种数
    int s;  //最多杀怪数
    while (cin >> n >> m >> k >> s) {
        vector<pair<int, int>> monsters;
        for (int i = 0; i < k; i++) {
            int a, b;  //经验值，忍耐度
            cin >> a >> b;
            monsters.push_back(make_pair(a, b));
        }
        vector<vector<int>> dp(m + 1, vector<int>(s + 1, 0));
        for (int z = 0; z < k; z++) {                        //怪种数
            for (int i = monsters[z].second; i <= m; i++) {  //忍耐度
                for (int j = 1; j <= s; j++) {               //最多杀怪数
                    dp[i][j] = max(dp[i][j], dp[i - monsters[z].second][j - 1] + monsters[z].first);
                }
            }
        }

        bool able = false;
        int cost = 0;
        for (; cost <= m; cost++) {
            if (dp[cost][s] >= n) {
                able = true;
                break;
            }
        }
        cout << (able ? m - cost : -1) << endl;
    }
    return 0;
}