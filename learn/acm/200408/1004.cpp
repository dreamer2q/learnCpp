#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

/*  

这题知道最小生成树的话，思路不会难。
但是我这一题卡了很久很久，每次都是超时，我以为是算法需要优化，然而我错了。
C语言处理结构体的时候效率非常的地下，我一开始就是开了一个结构体数组，
输入数据的时候对每一个结构体进行赋值，（我觉得就是卡在这里了，赋值是一个很耗时的操作，因为要用到内存）
此外，C语言对结构体赋值需要计算下标，加上结构体内成员的偏移，之后进行解引用，然后赋值。
这样一套下来，效率确实有些低。

哎，我自忖C语言学得还不错，但是碰到这个问题反倒是语言把我坑了一波。
看来我学得还是太肤浅了，没有深入内部，需要好好补一补这方面的缺漏。

by dreamer2q 2020年4月9日，21点50分
    --- 一次失败的做题经历
    
*/

#define N 101
int set[N];

int find(int x) {
    //if (set[x] == x) return x;
    //return set[x] = find(set[x]);
    while (set[x] != x) {  //查找根节点
        x = set[x];
    }
    return x;
}

void merge(int a, int b) {
    int pa = find(a);
    int pb = find(b);
    if (pa != pb)
        set[pa] = pb;
}

void makeSet(int n) {
    for (int i = 1; i <= n; i++)
        set[i] = i;
}

struct Edge {
    int i, j;
    int cost;
};

bool cmp(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}

int main() {
    int n, t;
    while (cin >> n) {
        makeSet(n);
        vector<Edge> edges;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int h;
                cin >> h;
                if (j > i) {
                    edges.push_back(Edge{i, j, h});
                }
            }
        }
        sort(edges.begin(), edges.end(), cmp);
        scanf("%d", &t);
        for (int i = 0; i < t; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            merge(a, b);
        }
        int min_cost = 0;
        for (auto& edge : edges) {
            int root_a = find(edge.i);
            int root_b = find(edge.j);
            if (root_a != root_b) {
                merge(edge.i, edge.j);
                min_cost += edge.cost;
            }
        }
        printf("%d\n", min_cost);
    }
}
