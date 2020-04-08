#include <iostream>

using namespace std;

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    int cases;
    cin >> cases;
    while (cases--) {
        int w, n;
        cin >> w >> n;
        int cost[2001], value[2001], index = 0;
        for (int i = 0; i < n; i++) {
            int c, v, num;
            cin >> c >> v >> num;
            //二进制优化
            int t = 1;
            while (num >= t) {
                cost[index] = t * c;
                value[index] = t * v;
                num -= t;
                t <<= 1;  //这里移动一位，表示*2,我好傻，一开始写成了2，呜呜呜
                index++;
            }
            if (num) {
                cost[index] = num * c;
                value[index] = num * v;
                index++;
            }
        }
        int dp[1001] = {0};
        for (int i = 0; i < index; i++) {
            for (int j = w; j >= cost[i]; j--) {
                dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
            }
        }
        cout << dp[w] << endl;
    }
    return 0;
}
