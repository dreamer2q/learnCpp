#include <stdio.h>
#include <algorithm>

#define NUM 1001

typedef struct {
    int ddl, score;
} homework;

homework hw[NUM];

bool cmp(homework a, homework b) {
    if (a.ddl != b.ddl) return a.ddl < b.ddl;
    return a.score > b.score;
}

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &hw[i].ddl);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &hw[i].score);
        }
        std::sort(hw, hw + n, cmp);
        int ans = 0;
        int day = 0;
        for (int i = 0; i < n; i++) {
            if (hw[i].ddl > day) {
                day++;
            } else {
                ans += hw[i].score;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}