#include <stdio.h>
#include <algorithm>

typedef struct {
    int sta, end;
} Item;

Item A[101];

bool cmp(Item &a, Item &b) {
    return a.end < b.end;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (0 == n) break;
        for (int i = 0; i < n; i++) {
            int ts, te;
            scanf("%d %d", &ts, &te);
            A[i].sta = ts;
            A[i].end = te;
        }
        std::sort(A, A + n, cmp);
        int cur = A[0].end;
        int counter = 1;
        for (int i = 1; i < n; i++) {
            if (cur <= A[i].sta) {
                cur = A[i].end;
                counter++;
            }
        }
        printf("%d\n", counter);
    }

    return 0;
}