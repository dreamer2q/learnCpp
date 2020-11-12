
#include <bits/stdc++.h>

using namespace std;

int bfs(int a, int b, vector<int>& floors, vector<bool>& visit) {
    queue<pair<int, int>> q;
    q.push(make_pair(a, 0));
    visit[a] = true;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur.first == b) {
            return cur.second;
        }
        int delta = floors[cur.first];
        if (cur.first + delta < floors.size() && !visit[cur.first + delta]) {
            q.push(make_pair(cur.first + delta, cur.second + 1));
            visit[cur.first + delta] = true;
        }
        if (cur.first - delta > 0 && !visit[cur.first - delta]) {
            q.push(make_pair(cur.first - delta, cur.second + 1));
            visit[cur.first - delta] = true;
        }
    }
    return -1;
}

int main() {
    int n, a, b;
    while (cin >> n, n) {
        cin >> a >> b;
        vector<int> floors;
        vector<bool> taken(n + 1, false);
        floors.push_back(-1);
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            floors.push_back(tmp);
        }
        cout << bfs(a, b, floors, taken) << endl;
    }
    return 0;
}