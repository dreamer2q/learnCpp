
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, s;
    while (cin >> n >> s) {
        //好好的写退出的条件，不要自以为是，浪费时间。
        if (n == 0 && s == 0) break;
        vector<pair<int, double>> sel;
        for (int i = 0; i < s; i++) {
            int cost;
            double prob;
            cin >> cost >> prob;
            sel.push_back(make_pair(cost, 1 - prob));
        }
        vector<double> dp(n + 1, 1);
        for (int i = 0; i < s; i++) {
            for (int j = n; j >= sel[i].first; j--) {
                dp[j] = min(dp[j], dp[j - sel[i].first] * sel[i].second);
            }
        }
        printf("%.1lf%%\n", (1 - dp[n]) * 100);
    }
    return 0;
}
