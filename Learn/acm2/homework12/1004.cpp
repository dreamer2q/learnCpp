
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n, n) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            ans ^= t;
        }
        printf("%s Win!\n", ans ? "Rabbit" : "Grass");
    }
    return 0;
}
