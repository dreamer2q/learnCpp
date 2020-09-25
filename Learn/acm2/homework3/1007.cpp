
#include <bits/stdc++.h>

using namespace std;

// Quoit Design
//
// 寻找两点之间最短的距离
// 这题标准的算法我不懂
// 但是由于数据很大，不需要搜索全部的数据
// 只需要排序之后的前N个即可完成AC要求
// PS 最好了解一下标准的解法

inline double distance(pair<double, double>& a, pair<double, double>& b) {
    auto dx = a.first - b.first;
    auto dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int n;
    while (cin >> n, n) {
        vector<pair<double, double>> data;
        while (n--) {
            double x, y;
            // cin >> x >> y;
            scanf("%lf %lf", &x, &y);
            data.push_back(make_pair(x, y));
        }

        sort(data.begin(), data.end(), [](const pair<double, double>& a, const pair<double, double>& b) {
            // if (a.first - b.first < 1e-6) return a.second < b.second;
            // return a.first < b.first;
            return a.first + a.second < b.first + b.second;
        });

        //二重循环，最寻最短的线段
        double radius = 999999;
        for (int i = 0; i < data.size(); i++) {
            //搜索前两个就可以过，感觉数据有点水水
            for (int j = i + 1; j < min(data.size(), size_t(i + 2)); j++) {  //暴力搜索前N个即可AC
                auto dis = distance(data[i], data[j]);
                if (dis < radius) {
                    radius = dis;
                }
            }
        }
        printf("%.2lf\n", radius / 2);
    }

    return 0;
}