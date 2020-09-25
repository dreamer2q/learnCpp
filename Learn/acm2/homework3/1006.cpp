
// Degree Sequence of Graph G
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> data;
        while (n--) {
            int tmp;
            cin >> tmp;
            data.push_back(tmp);
        }
        bool isGraph = true;
        for (int i = 0; i < data.size() && isGraph; i++) {
            sort(data.rbegin(), data.rend());
            if (data[0] < data.size()) {
                for (int j = 1; j <= data[0]; j++) {
                    data[j]--;
                    if (data[j] < 0) {
                        isGraph = false;
                        break;
                    }
                }
                data[0] = 0;
            } else {
                isGraph = false;
                break;
            }
        }
        cout << (isGraph ? "yes" : "no") << endl;
    }

    return 0;
}