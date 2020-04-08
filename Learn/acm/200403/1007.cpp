#include <cstdio>
#include <iostream>

using namespace std;

inline double max(double a, double b) { return a > b ? a : b; }

inline double calc(double a, double b) {
    return 1 - (1 - a) * (1 - b);
}

int main() {
    int m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;  //鬼畜，这里的m或n可能有一个为0
        int cost[10001];
        double probability[10001];
        for (int i = 0; i < n; i++) {
            cin >> cost[i] >> probability[i];
        }
        double dp[10001] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= cost[i]; j--) {
                dp[j] = max(dp[j], calc(dp[j - cost[i]], probability[i]));
            }
        }
        printf("%.1lf%%\n", dp[m] * 100);
    }

    return 0;
}