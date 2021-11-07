#include <bits/stdc++.h>

using namespace std;

// moving tables
// 贪心，寻找最多重叠

int main() {
    int test;
    cin >> test;
    while (test--) {
        int corride[401] = {0};
        int n;
        cin >> n;
        while (n--) {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);
            a = (a - 1) / 2;
            b = (b - 1) / 2;
            for (int i = a; i <= b; i++) {
                corride[i]++;
            }
        }
        auto result = max_element(begin(corride), end(corride));
        cout << *result * 10 << endl;
    }
    return 0;
}