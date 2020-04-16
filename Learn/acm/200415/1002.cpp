#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

const int N = 8;

int board[N][N];

struct pos {
    int x, y;
    int steps;
    // bool operator==(const pos& o) {
    //     return x == o.x && y == o.y;
    // }
    pos operator+(const pos& a) {
        return pos{
            x + a.x,
            y + a.y,
            steps + 1,
        };
    }
    friend bool operator==(const pos& a, const pos& b) {
        return a.x == b.x && a.y == b.y;
    }
};

pos dir[] = {
    {-2, -1},
    {-2, 1},
    {2, -1},
    {2, 1},
    {-1, -2},
    {-1, 2},
    {1, 2},
    {1, -2},
};

pos sp, ep;

inline int& v(const pos& p) {
    return board[p.x][p.y];
}
inline bool in(const pos& p) {
    return p.x >= 0 && p.x < N && p.y >= 0 && p.y < N;
}
int bfs() {
    memset(board, 0, sizeof(board));

    queue<pos> q;
    q.push(sp);
    v(sp) = 1;

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == ep) {
            return cur.steps;
        }

        //遍历所有子节点，最多8个
        for (const auto& d : dir) {
            auto nex = cur + d;
            if (in(nex) && v(nex) == 0) {
                v(nex) = 1;
                q.push(nex);
            }
        }
    }
    //error here
    return -1;
}
int main() {
    string a, b;

    while (cin >> a >> b) {
        sp = {
            a[0] - 'a',
            a[1] - '1',
        };
        ep = {
            b[0] - 'a',
            b[1] - '1',
        };
        int steps = bfs();
        printf("To get from %s to %s takes %d knight moves.\n", a.c_str(), b.c_str(), steps);
    }

    return 0;
}