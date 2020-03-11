#include <stdio.h>

int main() {
    int T;
    int P[200];
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 200 ; i++) {
            P[i] = 0;
        }
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a = (a - 1) / 2;
            b = (b - 1) / 2;
            if (a > b) {
                int tmp = a;
                a = b;
                b = tmp;
            }
            for (int k = a; k <= b; k++) {
                P[k]++;
            }
        }
        int ans = -1;
        for (int i = 0; i < 200; i++) {
            if (P[i] > ans) {
                ans = P[i];
            }
        }
        printf("%d\n", ans * 10);
    }

    return 0;
}