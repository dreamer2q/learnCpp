#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct pos {
    int x, y;
    int steps;
    pos operator+(const pos& a) {
        return pos{
            x + a.x,
            y + a.y,
            steps + 1,
        };
    }
    pos operator*(int n) const {
        return pos{
            x * n,
            y * n,
        };
    }
    friend bool operator==(const pos& a, const pos& b) {
        return a.x == b.x && a.y == b.y;
    }
};

pos dir[] = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
};

pos sp, ep;

int N, M;
inline bool in(const pos& p) {
    return p.x >= 0 && p.x < N && p.y >= 0 && p.y < M;
}

int board[11][11];
inline int& v(const pos& p) {
    return board[p.x][p.y];
}
int bfs() {
    queue<pos> q;
    q.push(sp);
    v(sp) = 'v';  //标记走过

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == ep) {
            return cur.steps;
        }
        for (const auto& d : dir) {
            auto nex = cur + d;
            if (!in(nex)) continue;
            if (v(nex) == 'v') continue;
            if (v(nex) == '*') {
                nex = cur + d * 2;
                if (!in(nex)) continue;
                if (v(nex) == 'v') continue;
                if (v(nex) == '*') continue;
            }
            v(nex) = 'v';  //标记为已经走过
            q.push(nex);
        }
    }
    //无路可走
    return -1;
}
int main() {
    while (cin >> N >> M) {
        memset(board, 0, sizeof(board));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c;
                cin >> c;
                board[i][j] = c;
            }
        }
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        sp = {
            x1 - 1,
            y1 - 1,
        };
        ep = {
            x2 - 1,
            y2 - 1,
        };
        cout << bfs() << endl;
    }
    return 0;
}