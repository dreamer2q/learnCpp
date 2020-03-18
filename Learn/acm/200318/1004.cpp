#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define min(a, b) ((a) > (b) ? (b) : (a))
#define sq(a) ((a) * (a))

int dp[2001][1001];

int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) == 2) {
        int data[2001];
        for (int i = 1; i <= n; i++) {
            scanf("%d", data + i);
        }
        std::sort(data + 1, data + n + 1);

        for (int i = 1; i <= k; i++) {
            for (int j = 2 * i; j <= n; j++) {
                if (j < 2 * i + 1) {
                    dp[j][i] = dp[j - 2][i - 1] + sq(data[j] - data[j - 1]);
                } else {
                    dp[j][i] = min(dp[j - 2][i - 1] + sq(data[j] - data[j - 1]), dp[j - 1][i]);
                }
            }
        }
        printf("%d\n", dp[n][k]);
    }
}