#include <bits/stdc++.h>

using namespace std;

struct State {
    int a, b, c, steps;

    bool operator<(const State& s) const {
        return (1000 * a + b) < (1000 * s.a + s.b);
    }

    bool operator==(const State& s) const {
        return a == s.a && b == s.b && c == s.c;
    }
};

bool match(const State& s) {
    if (s.a == 0 && s.b == s.c ||
        s.b == 0 && s.a == s.c ||
        s.c == 0 && s.a == s.b) {
        return true;
    }
    return false;
}

int bfs(State init, State s) {
    map<State, bool> visited;
    queue<State> q;
    q.push(init);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        visited[cur] = true;
        if (match(cur)) {
            return cur.steps;
        }
        if (cur.a != 0) {
            if (cur.b != s.b) {
                auto t = min(s.b - cur.b, cur.a);
                State nex = {cur.a - t, cur.b + t, cur.c, cur.steps + 1};
                if (!visited[nex]) {
                    q.push(nex);
                    visited[nex] = true;
                }
            }
            if (cur.c != s.c) {
                auto t = min(s.c - cur.c, cur.a);
                State nex = {cur.a - t, cur.b, cur.c + t, cur.steps + 1};
                if (!visited[nex]) {
                    q.push(nex);
                    visited[nex] = true;
                }
            }
        }
        if (cur.b != 0) {
            if (cur.a != s.a) {
                auto t = min(s.a - cur.a, cur.b);
                State nex = {cur.a + t, cur.b - t, cur.c, cur.steps + 1};
                if (!visited[nex]) {
                    q.push(nex);
                    visited[nex] = true;
                }
            }
            if (cur.c != s.c) {
                auto t = min(s.c - cur.c, cur.b);
                State nex = {cur.a, cur.b - t, cur.c + t, cur.steps + 1};
                if (!visited[nex]) {
                    q.push(nex);
                    visited[nex] = true;
                }
            }
        }
        if (cur.c != 0) {
            if (cur.a != s.a) {
                auto t = min(s.a - cur.a, cur.c);
                State nex = {cur.a + t, cur.b, cur.c - t, cur.steps + 1};
                if (!visited[nex]) {
                    q.push(nex);
                    visited[nex] = true;
                }
            }
            if (cur.b != s.b) {
                auto t = min(s.b - cur.b, cur.c);
                State nex = {cur.a, cur.b + t, cur.c - t, cur.steps + 1};
                if (!visited[nex]) {
                    q.push(nex);
                    visited[nex] = true;
                }
            }
        }
    }
    return -1;
}

int main() {
    int s, n, m;
    while (cin >> s >> n >> m) {
        if (s == 0 && n == 0 && m == 0) break;
        int ret = bfs({s, 0, 0, 0}, {s, n, m, 0});
        if (ret == -1) {
            cout << "NO" << endl;
        } else {
            cout << ret << endl;
        }
    }
    return 0;
}
