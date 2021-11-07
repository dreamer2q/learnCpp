#include <bits/stdc++.h>
using namespace std;

#define ll long long

int d[] = {2, 3, 5, 7};

int main() {
    ll n;
    while (cin >> n, n) {
        int count = 1;
        int ans[] = {1, 1, 1, 1};
        for (int i = 0; i < 4; i++) {
            for (; n % d[i] == 0; n /= d[i]) {
                ans[i]++;
            }
        }
        cout << ans[0] * ans[1] * ans[2] * ans[3] << endl;
    }
    return 0;
}
