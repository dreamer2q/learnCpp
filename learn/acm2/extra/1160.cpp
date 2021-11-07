#include <bits/stdc++.h>

using namespace std;

struct FatMouse {
    int seq;
    int weight;
    int speed;
};

//special judge
int dp[1100];

int main() {
    NULL;
    vector<FatMouse> mice;
    int index = 1;
    int w, m;
    while (cin >> w >> m) {
        mice.push_back({index++, w, m});
    }
    sort(mice.begin(), mice.end(), [](const FatMouse& a, const FatMouse& b) {
        if (a.weight == b.weight) {
            return a.speed < b.speed;
        }
        return a.weight > b.weight;
    });

    //dp speed from small to big
    vector<vector<int>> ans(mice.size());
    for (int i = 0; i < mice.size(); i++) {
        dp[i] = 1;
    }
    for (int i = 0; i < mice.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (mice[i].speed > mice[j].speed) {
                // dp[i] = max(dp[i], dp[j] + 1);
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    ans[i].push_back(mice[j].seq);
                }
            }
            ans[i].push_back(mice[i].seq);
        }
    }

    int ret = 0;
    for (int i = 0; i < mice.size(); i++) {
        if (dp[i] > dp[ret]) {
            ret = i;
        }
    }
    cout << dp[ret] << endl;
    for (auto i : ans[ret]) {
        cout << i << endl;
    }

    return 0;
}