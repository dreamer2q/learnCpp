#include <bits/stdc++.h>

using namespace std;

vector<string> gmap;
int n;   //行数
int m;   //列数
int t;   //时间
int dx;  //终点x
int dy;  //终点y
bool solved = false;

char& visit(int x, int y) {
    return gmap[x][y];
}

bool check(int x, int y) {  //行，列
    if (x >= 0 && y >= 0 && x < n && y < m) {
        auto block = visit(x, y);
        return !solved && block != 'X';
    }
    return false;
}

// dfs 重点，剪枝
void dfs(int x, int y, int steps) {
    //剪纸2
    int test = (t - steps) - (abs(x - dx) + abs(y - dy));
    if (test < 0 || test % 2) return;

    switch (visit(x, y)) {
        case 'D':
            if (steps == t) solved = true;
            break;
        case '.':
        case 'S':
            visit(x, y) = 'X';
            if (check(x + 1, y)) dfs(x + 1, y, steps + 1);
            if (check(x - 1, y)) dfs(x - 1, y, steps + 1);
            if (check(x, y + 1)) dfs(x, y + 1, steps + 1);
            if (check(x, y - 1)) dfs(x, y - 1, steps + 1);
            visit(x, y) = '.';
            break;
        case 'X':
            break;
    }
}

int main() {
    while (cin >> n >> m >> t) {
        if (n == 0 && m == 0 && t == 0) break;
        gmap.clear();
        solved = false;
        int sx, sy,
            w = 0;
        for (int i = 0; i < n; i++) {
            string line;
            for (int j = 0; j < m; j++) {
                char tmp;
                cin >> tmp;
                line.push_back(tmp);
                switch (tmp) {
                    case '.':
                        break;
                    case 'X':
                        w++;
                        break;
                    case 'S':
                        sx = i;
                        sy = j;
                        break;
                    case 'D':
                        dx = i;
                        dy = j;
                        break;
                }
            }
            gmap.push_back(line);
        }
        //剪1
        if (n * m - w <= t) {
            std::cout << "NO" << endl;
            continue;
        }
        dfs(sx, sy, 0);
        std::cout << (solved ? "YES" : "NO") << endl;
    }

    return 0;
}
