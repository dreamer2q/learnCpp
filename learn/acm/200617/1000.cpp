/*
 * File Created: Wednesday, 17th June 2020 6:25:50 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 17th June 2020 6:36:32 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    int C;
    cin >> C;
    while (C--) {
        int n;
        cin >> n;
        double avg = 0.0;
        int count = 0;
        vector<int> score;
        for (int i = 0; i < n; i++) {
            int s;
            cin >> s;
            score.push_back(s);
        }
        avg = accumulate(score.begin(), score.end(), 0, [](const int a, const int b) {
            return a + b;
        });
        avg /= n;
        for_each(score.begin(), score.end(), [&](const int s) {
            if (s >= avg) {
                count++;
            }
        });
        printf("%.2lf %d\n", avg, count);
    }
    return 0;
}