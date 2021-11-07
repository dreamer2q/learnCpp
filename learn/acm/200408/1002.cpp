
/* 

感谢 https://blog.csdn.net/hy1405430407/article/details/46126365 提供的数据

 */

#include <cstdio>
#include <iostream>

using namespace std;

#define N 10001
int set[N];
int num[N];

int find(int x) {
    int r = x;
    while (set[r] != r)
        r = set[r];
    return r;
}

bool merge(int a, int b) {
    if (set[b] != 0 && set[b] != b) return false;   //b 不能有父节点
    if (set[a] != 0 && b == find(a)) return false;  //b 不能有 a 这个儿子
    set[b] = a;                                     //让 a 成为 b 的父节点
    if (set[a] == 0) set[a] = a;
    return true;
}
int main() {
    int a, b, cases = 1;
    bool tree = true;
    int index = 0;

    while (cin >> a >> b) {
        if (a < 0 && b < 0) break;
        if (a == 0 && b == 0) {
            if (tree) {
                int counter = 0;
                for (int i = 1; i < N; i++) {
                    if (set[i] == i) counter++;
                    set[i] = 0;
                }
                if (counter > 1) tree = false;
            } else {
                for (int i = 1; i < N; i++) set[i] = 0;
            }
            printf("Case %d is %s\n", cases++, (tree ? "a tree." : "not a tree."));
            tree = true;
            index = 0;
            continue;
        }
        num[index++] = a;
        if (tree && !merge(a, b)) {
            tree = false;
        }
    }
    return 0;
}