#include <bits/stdc++.h>

using namespace std;

char mmp[10][10];
int dirs[][2] = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
};

int si, sj, ei, ej;
int n, m, t;
bool escaped = false;

void dfs(int i, int j, int ct) {
    if (i <= 0 || j <= 0 || i > n || j > m)
        return;
    if (i == ei && j == ej && ct == t)
        escaped = true;
    if (escaped)
        return;
    int tmp = (t - ct) - abs(i - ei) - abs(j - ej);

    if (tmp < 0 || (tmp % 2 == 1))
        return;
    for (int z = 0; z < 4; z++) {
        if (mmp[i + dirs[z][0]][j + dirs[z][1]] != 'X') {
            mmp[i + dirs[z][0]][j + dirs[z][1]] = 'X';

            dfs(i + dirs[z][0], j + dirs[z][1], ct + 1);

            mmp[i + dirs[z][0]][j + dirs[z][1]] = '.';
        }
    }
}

int main() {
    while (cin >> n >> m >> t) {
        if (n == 0 && m == 0 && t == 0) break;
        int wall = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> mmp[i][j];
                switch (mmp[i][j]) {
                    case 'S':
                        si = i;
                        sj = j;
                        break;
                    case 'D':
                        ei = i;
                        ej = j;
                        break;
                    case 'X':
                        wall++;
                        break;
                }
            }
        }

        if (n * m - wall <= t) {
            cout << "NO" << endl;
            break;
        }

        escaped = false;
        mmp[si][sj] = 'X';
        dfs(si, sj, 0);
        if (escaped) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}