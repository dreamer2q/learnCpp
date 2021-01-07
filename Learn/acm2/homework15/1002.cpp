
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n, n) {
        unordered_map<string, int> map;
        string key;
        for (int i = 0; i < n; i++) {
            cin >> key;
            map[key]++;
        }
        int count = 0;
        for (const auto &item : map) {
            if (item.second > count) {
                key = item.first;
                count = item.second;
            }
        }
        cout << key << endl;
    }
    return 0;
}
