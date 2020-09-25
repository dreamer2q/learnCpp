
#include <bits/stdc++.h>

using namespace std;

// 题目： 今年暑假不AC
// 类似于寻找最长子序列
// 对于电视节目的时间排序
// 需要确保最早结束的节目排在前面
// 因为最长子序列一定包含最早结束的电视节目
// 有这个性质就可以进行贪心了，每一次都寻找最早结束的节目
// 对每一个走一遍，最后就是最优解。

int main() {
    int n;
    while (cin >> n, n) {
        vector<pair<int, int>> data;
        while (n--) {
            int start, end;
            cin >> start >> end;
            data.push_back(make_pair(start, end));
        }
        sort(data.begin(), data.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.second == b.second) return a.first > b.first;
            return a.second < b.second;
        });
        int timeline = 0;
        int count = 0;
        for (const auto& item : data) {
            if (item.first >= timeline) {
                count++;
                timeline = item.second;
            }
        }
        cout << count << endl;
    }

    return 0;
}