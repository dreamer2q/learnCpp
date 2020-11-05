
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, v;
        cin >> n >> v;
        vector<int> value;
        vector<int> volume;
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            value.push_back(tmp);
        }
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            volume.push_back(tmp);
        }
        vector<int> dp(v + 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j = v; j >= volume[i]; j--) {
                dp[j] = max(dp[j], dp[j - volume[i]] + value[i]);
            }
        }
        cout << dp[v] << endl;
    }
    return 0;
}
