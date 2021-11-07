#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

struct {
    int val;
    int ans;
} A[101][101];

int dp(int y, int x, int depth) {
    if (y == depth - 1) {
        return A[y][x].val;
    }
    if (A[y][x].ans != -1) {
        return A[y][x].ans;
    }
    return (A[y][x].ans = A[y][x].val + max(dp(y + 1, x, depth), dp(y + 1, x + 1, depth)));
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i + 1; j++) {
                int val;
                scanf("%d", &val);
                A[i][j].val = val;
                A[i][j].ans = -1;
            }
        }
        printf("%d\n", dp(0, 0, N));
    }
}
