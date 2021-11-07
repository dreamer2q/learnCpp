#include <cstring>
#include <iostream>
using namespace std;

/*
robot motion

by dreamer2q

思路，
直接模拟机器人的前进
对每一步进行标记
如果出现之前走的路线，则说明出现循环，结束
如果走出了格子，说明直接走出去了，结束。
*/

int main() {
    int vis[13][13];
    char mmp[11][11];
    int width, height;

    while (cin >> height >> width) {
        if (width == 0 && height == 0)
            break;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < width + 2; i++) {
            vis[0][i] = 1;
            vis[width + 1][i] = 1;
        }
        for (int i = 0; i < height + 2; i++) {
            vis[i][0] = 1;
            vis[i][height + 1] = 1;
        }
        int lx = 1, ly = 1;
        cin >> lx;
        for (int j = 1; j <= height; j++) {
            for (int i = 1; i <= width; i++) {
                cin >> mmp[i][j];
            }
        }
        int cx = lx, cy = ly;
        while (!vis[cx][cy]) {
            vis[cx][cy] = 1 + vis[lx][ly];
            lx = cx;
            ly = cy;
            switch (mmp[cx][cy]) {
                case 'N':
                    cy--;
                    break;
                case 'S':
                    cy++;
                    break;
                case 'W':
                    cx--;
                    break;
                case 'E':
                    cx++;
                    break;
            }
        }
        if (cx <= 0 || cx > width || cy <= 0 || cy > height) {
            cout << vis[lx][ly] << " step(s) to exit" << endl;
        } else {
            int lps = vis[lx][ly] - vis[cx][cy] + 1;
            int s = vis[lx][ly] - lps;
            cout << s << " step(s) before a loop of " << lps << " step(s)" << endl;
        }
    }
    return 0;
}