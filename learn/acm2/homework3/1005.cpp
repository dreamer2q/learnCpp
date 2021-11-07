#include <bits/stdc++.h>

using namespace std;

// 田忌赛马
// 已知敌方马匹的好坏和出场顺序如何调整自己马匹的出场顺序?
// 如何进行贪心求最优解？

int main() {
    int n;
    while (cin >> n, n) {
        vector<int> tian;
        vector<int> king;
        int speed;
        for (int i = 0; i < n; i++) {
            cin >> speed;
            tian.push_back(speed);
        }
        for (int i = 0; i < n; i++) {
            cin >> speed;
            king.push_back(speed);
        }
        sort(king.rbegin(), king.rend());
        sort(tian.rbegin(), tian.rend());

        pair<int, int> pT = make_pair(0, n - 1), pK = make_pair(0, n - 1);
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (tian[pT.first] > king[pK.first]) {  //田忌的最快的🐎比King最快的快，赢一场
                result++;
                pT.first++;
                pK.first++;
            } else if (tian[pT.first] < king[pK.first]) {  //田忌最快的🐎比king最快的慢，用最差的🐎输一场
                result--;
                pT.second--;
                pK.first++;
            } else {
                //两者的🐎一样快，是否平局
                if (tian[pT.second] > king[pK.second]) {  //田忌最慢的🐎比king最慢的快，赢一场
                    result++;
                    pT.second--;
                    pK.second--;
                } else if (tian[pT.second] <= king[pK.second]) {  // 不论结果如何，用田忌最慢的🐎换King的一匹好🐎
                    result -= tian[pT.second] < king[pK.first];
                    pT.second--;
                    pK.first++;
                }
            }
        }
        cout << result * 200 << endl;
    }
    return 0;
}