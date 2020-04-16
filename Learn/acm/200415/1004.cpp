#include <cstdio>
#include <iostream>
#include <queue>

/*
难得一次把作业做完了
*/

using namespace std;

int castle[50][50][50];
int A, B, C, T;
struct pos {
    int x, y, z;
    int steps;

    bool operator==(const pos& p) {
        return x == p.x && y == p.y && z == p.z;
    }
    pos operator+(const pos& p) {
        return pos{
            x + p.x,
            y + p.y,
            z + p.z,
            steps + 1,
        };
    }
};
//x,y,z
pos dir[] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1},
};

inline int& v(const pos& p) {
    return castle[p.x][p.y][p.z];
}
inline bool in(const pos& p) {
    return p.x >= 0 && p.x < A &&
           p.y >= 0 && p.y < B &&
           p.z >= 0 && p.z < C;
}
int bfs() {
    queue<pos> q;
    pos start{0, 0, 0};
    pos end{A - 1, B - 1, C - 1};
    q.push(start);
    v(start) = 1;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == end) {
            return cur.steps;
        }

        //find all sub-nodes, expand our search queue
        for (const auto& d : dir) {
            auto nex = cur + d;
            if (in(nex) && v(nex) == 0) {
                v(nex) = 1;
                q.push(nex);
            }
        }
    }
    return -1;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        cin >> A >> B >> C >> T;
        for (int i = 0; i < A; i++) {
            for (int j = 0; j < B; j++) {
                for (int z = 0; z < C; z++) {
                    scanf("%d", &castle[i][j][z]);
                }
            }
        }
        int steps = bfs();
        if (steps > T) steps = -1;
        cout << steps << endl;
    }
    return 0;
}
