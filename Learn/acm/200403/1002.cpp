#include <cstring>
#include <iostream>
using namespace std;

inline unsigned int min(unsigned int a, unsigned int b) { return a > b ? b : a; }

int main() {
    int cases;
    cin >> cases;
    while (cases--) {
        int pig, pigcoin;
        cin >> pig >> pigcoin;
        int w = pigcoin - pig;  //total coin weight
        int n;                  //n种货币, 1<=n<=500
        cin >> n;
        int value[501], weight[501];
        for (int i = 0; i < n; i++) {
            cin >> value[i] >> weight[i];
        }
        unsigned int dp[10001];
        for (int i = 0; i < 10001; i++) {
            dp[i] = -60000;
        }
        //memset(dp, (unsigned int)-60000, sizeof(dp));
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = weight[i]; j <= w; j++) {
                dp[j] = min(dp[j], dp[j - weight[i]] + value[i]);
            }
        }
        if (dp[w] == -60000) {
            cout << "This is impossible." << endl;
        } else {
            cout << "The minimum amount of money in the piggy-bank is " << dp[w] << "." << endl;
        }
    }

    return 0;
}