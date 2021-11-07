#include <iostream>

using namespace std;

int S[14], ans[14], vis[50];
int k;
void dfs(int steps) {
    if (steps == 6) {
        for (int i = 0; i < 5; i++) {
            cout << ans[i] << " ";
        }
        cout << ans[5] << endl;
    }

    for (int i = 0; i < k; i++) {
        int ele = S[i];
        if (!vis[ele]) {
            if (steps > 0) {
                if (ele < ans[steps - 1])
                    continue;
            }
            vis[ele] = 1;
            ans[steps] = ele;
            dfs(steps + 1);
            vis[ele] = 0;
        }
    }
}

int main() {
    cin >> k;
    while (1) {
        for (int i = 0; i < k; i++)
            cin >> S[i];
        dfs(0);
        cin >> k;
        if (k != 0)
            cout << endl;
        else
            break;
    }

    return 0;
}