#include <memory.h>
#include <stdio.h>

int A[100001][14];

#define max(a, b) ((a) > (b) ? (a) : (b))

int maxs(int a, int b, int c) {
    return max(a, max(b, c));
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        memset(A, 0, sizeof(A));
        int a, t, maxT = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &a, &t);
            A[t][a + 1]++;
            if (t > maxT) maxT = t;
        }
        for (int i = maxT - 1; i >= 0; i--) {
            for (int j = 1; j <= 11; j++) {
                A[i][j] += maxs(A[i + 1][j - 1], A[i + 1][j], A[i + 1][j + 1]);
            }
        }
        printf("%d\n", A[0][6]);
    }
}
