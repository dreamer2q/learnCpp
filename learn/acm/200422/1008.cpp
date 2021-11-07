#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

struct pos {
    int x, y;
    friend pos operator+(const pos& a, const pos& b) {
        return {a.x + b.x, a.y + b.y};
    }
    friend int operator-(const pos& a, const pos& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }
    friend pos operator*(const pos& a, int t) {
        return pos{a.x * t, a.y * t};
    }
};

pos dirs[] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
};

int N, K;
int mmp[101][101];
int dp[101][101];
inline bool in(const pos& p) {
    return p.x >= 0 && p.x < N && p.y >= 0 && p.y < N;
}
inline int& m(const pos& p) {
    return mmp[p.x][p.y];
}
inline int& d(const pos& p) {
    return dp[p.x][p.y];
}

int dfs(pos cur) {
    if (d(cur) != -1)
        return d(cur);
    d(cur) = m(cur);
    for (const auto& dir : dirs) {
        for (int i = 1; i <= K; i++) {
            auto nex = cur + dir * i;
            if (!in(nex) || m(nex) <= m(cur))
                continue;
            d(cur) = max(d(cur), m(cur) + dfs(nex));
        }
    }
    return d(cur);
}

int main() {
    while (cin >> N >> K) {
        if (N == -1 && K == -1)
            break;
        for (int i = 0; i < N; i++) {      //Y
            for (int j = 0; j < N; j++) {  //X
                cin >> mmp[j][i];
            }
        }
        memset(dp, -1, sizeof(dp));
        cout << dfs({0, 0}) << endl;
    }
    return 0;
}