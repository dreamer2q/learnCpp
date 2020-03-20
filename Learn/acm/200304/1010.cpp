#include <stdio.h>
#include <string.h>
#include <algorithm>

/*
Frogs' Neighborhood
*/

/*
2020年3月20日
这段代码有问题，未通过测试，目前不知道哪里有错。
*/

bool cmp(int a, int b) {
    return a > b;
}

bool drawable(int *a, int n) {
    for (int i = 0; i < n; i++) {
        std::sort(a, a + n, cmp);
        for (int j = 1; j <= a[0]; j++) {
            a[j]--;
            if (a[j] < 0) return false;
        }
        a[0] = 0;
    }
    return true;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n;
        scanf("%d", &n);
        int a[11], b[11];
        for (int i = 0; i < n; i++) {
            int tmp;
            scanf("%d", &tmp);
            a[i] = b[i] = tmp;
        }
        bool flag = drawable(b, n);
        if (!flag) {
            printf("NO\n\n");
            continue;
        }
        printf("YES\n");
        int d[11][11];
        memset(d, 0, sizeof(d));
        for (int i = 0; i < n; i++) {
            if (a[i] <= 0) continue;
            for (int j = i + 1; a[i] > 0 && j < n; j++) {
                if (a[j] > 0 && a[i] > 0) {
                    a[j]--;
                    a[i]--;
                    d[j][i] = d[i][j] = 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", d[i][j]);
            }
            printf("\n");
        }
        if (cases != 0)
            printf("\n");
    }

    return 0;
}