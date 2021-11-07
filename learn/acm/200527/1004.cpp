#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        map<string, int> m;
        while (n--) {
            string word;
            cin >> word;
            m[word]++;
        }
        string ans;
        for (const auto& e : m) {
            if (e.second > m[ans]) {
                ans = e.first;
            }
        }
        cout << ans << endl;
    }

    return 0;
}