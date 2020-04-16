#include <iostream>

using namespace std;

#define N 10000000
int set[N + 1];
int num[N + 1];
int max_num = 0;

inline int find(int x) {
    if (set[x] == 0) return x;
    set[x] = find(set[x]);  //更新路径，递归
    return set[x];
}

inline void merge(int a, int b) {
    int pa = find(a), pb = find(b);
    if (pa == pb) return;                               //已经是同一个集合
    set[pb] = pa;                                       //b 合并到 a 集合
    num[pa] += num[pb];                                 //更新集合a 元素的数量
    max_num = (max_num > num[pa] ? max_num : num[pa]);  //更新最大集合的数量
}

inline void makeSet() {
    for (int i = 1; i <= N; i++) {
        set[i] = 0;
        num[i] = 1;
    }
}

int main() {
    int n;
    while (cin >> n) {
        makeSet();
        max_num = 1;
        while (n--) {
            int a, b;
            //需要读入大量数据的时候，实用C语言的函数，cpp的忒慢了，直接超时
            scanf("%d %d", &a, &b);
            merge(a, b);
        }
        printf("%d\n", max_num);
    }
    return 0;
}
