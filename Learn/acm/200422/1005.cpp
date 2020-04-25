#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

char mmp[100][100];
int width, height;
bool vis[100][100];

//x,y
int dirs[][2] = {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1},
};

inline bool in(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool dfs(int sx, int sy) {
    if (!in(sx, sy))
        return false;
    if (vis[sx][sy])
        return false;
    if (mmp[sx][sy] != '@')
        return false;
    vis[sx][sy] = true;
    for (const auto& d : dirs) {
        int nx = sx + d[0];
        int ny = sy + d[1];
        if (in(nx, ny) && !vis[nx][ny] && mmp[nx][ny] == '@')
            dfs(nx, ny);
    }
    return true;
}

struct pos {
    int x, y;
};

int search() {
    int counter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            counter += dfs(j, i);
        }
    }
    return counter;
}

int main() {
    while (cin >> height >> width) {
        if (height == 0 || width == 0)
            break;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cin >> mmp[j][i];
            }
        }
        cout << search() << endl;
    }

    return 0;
}