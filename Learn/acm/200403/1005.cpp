#include <iostream>

using namespace std;

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    int value[] = {150, 200, 350};

    int cases;
    cin >> cases;

    while (cases--) {
        int w;
        cin >> w;
        int dp[10001] = {0};
        for (int i = 0; i < sizeof(value) / sizeof(value[0]); i++) {
            for (int j = value[i]; j <= w; j++) {
                dp[j] = max(dp[j], dp[j - value[i]] + value[i]);
            }
        }
        cout << w - dp[w] << endl;
    }

    return 0;
}