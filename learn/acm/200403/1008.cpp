#include <iostream>
using namespace std;
#define inf 10000000

inline int max(int a, int b) { return a > b ? a : b; }

/*
二位费用的背包，第二维由最多取多少件隐含给出的。
*/

int main() {
    /*
    由于经验值不一定刚刚好满足，可能有一点超出，因此将经验值作为价值进行dp
    然后从结果中寻早满足经验值的最小忍耐度代价
    */
    int n, m, k, s;
    //          经验，忍耐，总数，杀怪数
    while (cin >> n >> m >> k >> s) {
        int value[101], cost[101];
        for (int i = 0; i < k; i++) {
            cin >> value[i] >> cost[i];
        }
        int dp[101][101] = {0};  //dp[i][j] 代表忍耐度【i】最大杀怪数【j】,所获得的最大经验值

        for (int i = 0; i < k; i++) {
            for (int j = cost[i]; j <= m; j++) {
                for (int z = 1; z <= s; z++) {
                    dp[j][z] = max(dp[j][z], dp[j - cost[i]][z - 1] + value[i]);
                }
            }
        }

        //搜寻结果，未找到输出-1
        if (dp[m][s] < n) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i <= m; i++) {
                if (dp[i][s] >= n) {
                    cout << m - i << endl;
                    break;
                }
            }
        }
    }
    return 0;
}