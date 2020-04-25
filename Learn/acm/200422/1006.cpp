#include <iostream>

using namespace std;

/*
Accepted Necklace
普普通通的二维01背包问题
*/

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    int cas;
    cin >> cas;
    while (cas--) {
        int n, k;
        cin >> n >> k;
        int cost[22], value[22];
        for (int i = 0; i < n; i++) {
            cin >> value[i] >> cost[i];
        }
        int w;
        cin >> w;
        int dp[1100][22] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = w; j >= cost[i]; j--) {  //代价
                for (int z = 1; z <= k; z++) {    //件数
                                                  //状态转移
                    dp[j][z] = max(dp[j][z], dp[j - cost[i]][z - 1] + value[i]);
                }
            }
        }
        cout << dp[w][k] << endl;
    }

    return 0;
}