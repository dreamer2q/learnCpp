#include <iostream>

using namespace std;

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    int n;
    while (cin >> n) {
        int value[101], cost[101];
        for (int i = 0; i < n; i++) {
            cin >> value[i] >> cost[i];
        }
        int w;
        cin >> w;
        int dp[100001] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = cost[i]; j <= w; j++) {
                dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
            }
        }
        cout << dp[w] << endl;
    }

    return 0;
}