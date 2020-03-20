#include <stdio.h>
#include <algorithm>

int cmp(int a, int b) {
    return a > b;
}

int main() {
    int T;
    scanf("%d", &T);

    int A[1001];
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", A + i);
        }
        bool flag = true;
        for (int i = 0; i < n; i++) {
            std::sort(A, A + n, cmp);
            for (int j = 1; j <= A[0]; j++) {
                A[j]--;
                if (A[j] < 0) {
                    flag = false;
                    goto over;
                }
            }
            A[0] = 0;
        }
    over:
        printf("%s\n", flag ? "yes" : "no");
    }

    return 0;
}