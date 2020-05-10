#include <iostream>
#include <queue>

using namespace std;

int ST[1111];
void proc(int m, int n) {
    for (int i = 0; i < m; i++) {
        bool PFlag = true;
        for (int j = 1; j <= n; j++) {
            int t = i - j;
            if (t < 0)
                break;
            if (ST[t] == -1)
                PFlag = false;
        }
        ST[i] = PFlag ? -1 : 1;
    }
}
int stat(int n) {
    if (n < 0) return -1;
    return ST[n];
}

int main() {
    int m, n;
    while (cin >> m >> n) {
        proc(m, n);
        queue<int> ans;
        for (int i = 1; i <= n; i++) {
            if (stat(m - i) == -1) {
                ans.push(i);
            }
        }
        if (ans.empty()) {
            cout << "none" << endl;
        } else {
            while (!ans.empty()) {
                cout << ans.front();
                if (ans.size() != 1) {
                    cout << " ";
                }
                ans.pop();
            }
            cout << endl;
        }
    }
    return 0;
}