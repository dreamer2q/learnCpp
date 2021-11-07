#include <stdio.h>

int main() {
    int n;
    int F[1001];
    int A[1001];
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            int tmp;
            scanf("%d", &tmp);
            F[i] = tmp;
            A[i] = tmp;
        }
        int m = F[0];
        for (int i = 1; i < n; i++) {
            int tmx = 0;
            for (int j = 0; j < i; j++) {
                if (F[i] > F[j] && A[j] > tmx) {
                    tmx = A[j];
                }
            }
            A[i] += tmx;
            if (A[i] > m) m = A[i];
        }
        printf("%d\n", m);
    }

    return 0;
}