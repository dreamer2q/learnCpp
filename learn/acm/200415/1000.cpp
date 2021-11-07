#include <iostream>
#include <queue>

const int N = 2001;

using namespace std;

int mfloor[N];

struct pos {
    int level;
    int steps;
};

void bfs(int a, int b, int n) {
    int visited[N] = {0};

    queue<pos> q;
    q.push({a, 0});
    visited[a] = 1;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur.level == b) {
            cout << cur.steps << endl;
            return;
        }

        //注意，这里我们需要考察存在的子节点，并且使用visited数组来剪枝

        //UP
        pos nex = {
            cur.level + mfloor[cur.level],
            cur.steps + 1,
        };
        if (nex.level <= n && visited[nex.level] == 0) {
            visited[nex.level] = 1;
            q.push(nex);
        }
        //DOWN
        nex = {
            cur.level - mfloor[cur.level],
            cur.steps + 1,
        };
        if (nex.level >= 1 && visited[nex.level] == 0) {
            visited[nex.level] = 1;
            q.push(nex);
        }
    }
    cout << -1 << endl;
}

int main() {
    int n, a, b;
    while (cin >> n) {
        if (0 == n) break;
        cin >> a >> b;
        for (int i = 1; i <= n; i++) {
            cin >> mfloor[i];
        }
        bfs(a, b, n);
    }
    return 0;
}