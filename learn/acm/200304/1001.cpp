#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

struct S {
    int JavaBean;
    int CatFood;
    double ratio;
} A[2001];

int cmp(const void* a, const void* b) {
    return (((struct S*)a)->ratio < ((struct S*)b)->ratio) ? 1 : -1;
}

int main() {
    int food, N;
    while (scanf("%d %d", &food, &N) == 2) {
        if (food < 0 || N < 0) break;

        double ans = 0.0;
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &A[i].JavaBean, &A[i].CatFood);
            if (A[i].CatFood == 0) {  //白给的
                ans += A[i].JavaBean;
                i--;
                N--;
                continue;
            }
            A[i].ratio = double(A[i].JavaBean) / A[i].CatFood;
        }

        qsort(A, N, sizeof(struct S), cmp);

        for (int i = 0; food > 0 && i < N; i++) {
            if (food >= A[i].CatFood) {
                ans += A[i].JavaBean;
                food -= A[i].CatFood;
            } else {
                ans += food * A[i].ratio;
                break;
            }
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}
