#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n, n) {
        vector<int> C;
        vector<int> J;
        int tmp;
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            C.push_back(tmp);
        }
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            J.push_back(tmp);
        }
        sort(C.begin(), C.end());
        sort(J.begin(), J.end());
        pair<int, int> result;
        for (int i = 0; i < n; i++) {
            if (C[i] > J[i]) {
                result.first += 2;
            } else if (C[i] < J[i]) {
                result.second += 2;
            } else {
                result.first++;
                result.second++;
            }
        }
        cout << result.first << " vs " << result.second << endl;
    }

    return 0;
}