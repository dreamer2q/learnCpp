#include <iostream>

using namespace std;

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int cases;
    cin >> cases;
    while (cases--) {
        int dp[1001] = {0};
        int value[1001] = {0};
        int volumn[1001] = {0};
        int n, v;
        cin >> n >> v;
        for (int i = 0; i < n; i++) {
            cin >> value[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> volumn[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = v; j >= volumn[i]; j--) {
                dp[j] = max(dp[j], dp[j - volumn[i]] + value[i]);
            }
        }
        cout << dp[v] << endl;
    }

    return 0;
}