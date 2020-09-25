
#include <bits/stdc++.h>
using namespace std;

// doing homework again
// 做个作业也得贪心一下

struct Homework {
    int ddl, score;
    bool missed;
};

//TODO 这是一个错误的代码
//主要还是了解一下贪心的策略
//思路掌握了就好

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, tmp;
        cin >> n;
        vector<pair<int, int>> data;
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            data.push_back(make_pair(tmp, 0));
        }
        for (int i = 0; i < n; i++) {
            cin >> data[i].second;
        }
        sort(begin(data), end(data), [](const pair<int, int>& a, const pair<int, int> b) {
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });
        int result = 0, homework = 0;
        for (int day = 1; day <= n; day++) {
            if (day <= data[homework++].first) {
                while (homework < n && data[homework].first <= day) {
                    result += data[homework].second;
                    homework++;
                }
            }
        }
        cout << result << endl;
    }

    return 0;
}