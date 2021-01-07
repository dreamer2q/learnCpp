#include <bits/stdc++.h>

using namespace std;

const int lowbond = 1;
const int highbond = 100;

int main() {
    int sqr[101];
    for (int i = 0; i < 101; i++) {
        sqr[i] = i * i;
    }
    int a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        if (a > 0 && b > 0 && c > 0 && d > 0 ||
            a < 0 && b < 0 && c < 0 && d < 0) {
            cout << 0 << endl;
            continue;
        }
        unordered_map<int, int> result_map;
        for (int x1 = lowbond; x1 <= highbond; x1++) {
            for (int x2 = lowbond; x2 <= highbond; x2++) {
                int key = -(a * sqr[x1] + b * sqr[x2]);
                result_map[key]++;
            }
        }
        int ans_count = 0;
        for (int x3 = lowbond; x3 <= highbond; x3++) {
            for (int x4 = lowbond; x4 <= highbond; x4++) {
                int key = c * sqr[x3] + d * sqr[x4];
                ans_count += result_map[key];
            }
        }
        cout << 16 * ans_count << endl;
    }
    return 0;
}
