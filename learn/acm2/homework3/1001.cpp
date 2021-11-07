#include <bits/stdc++.h>

using namespace std;

// fatmouse trade
// 贪心

int main() {
    int m, n;
    while (cin >> m >> n) {
        if (m == -1 && n == -1) break;
        vector<pair<int, int>> trades;
        int javaBean, catFood;
        double sum = 0;
        while (n--) {
            cin >> javaBean >> catFood;
            if (catFood == 0) {
                sum += javaBean;
            } else {
                trades.push_back(make_pair(javaBean, catFood));
            }
        }
        sort(trades.begin(), trades.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            double left = (double)a.first / a.second;
            double right = (double)b.first / b.second;
            return left > right;
        });
        for (const auto& trade : trades) {
            if (trade.second <= m) {
                sum += trade.first;
                m -= trade.second;
            } else {
                sum += trade.first * double(m) / trade.second;
                break;
            }
        }
        printf("%.3lf\n", sum);
    }

    return 0;
}