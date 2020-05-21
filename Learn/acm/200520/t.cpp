#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int c1[10000];
int c2[10000];
int main() {
    int i, j, k, s, di;
    int n;
    int v[101], m[101];
    while (scanf("%d", &n), n) {
        s = 0;
        for (i = 1; i <= n; i++) {
            scanf("%d%d", &v[i], &m[i]);
            s += v[i] * m[i];
        }
        if (s % 3 == 0) {
            di = s / 3;
            memset(c1, 0, sizeof(c1));
            memset(c2, 0, sizeof(c2));
            for (i = 0; i <= m[1]; i++) {
                c1[i * v[1]] = 1;
            }
            for (i = 2; i <= n; i++) {
                for (j = 0; j <= s; j++) {
                    for (k = 0; k + j <= s && k <= v[i] * m[i]; k += v[i]) {
                        c2[k + j] += c1[j];
                        if (c2[k + j] > 10000) {
                            c2[k + j] %= 10000;
                        }
                    }
                }
                for (j = 0; j <= s; j++) {
                    c1[j] = c2[j];
                    c2[j] = 0;
                }
            }
            if (c1[di]) {
                printf("%d\n", c1[di]);
            } else
                printf("sorry\n");

        } else
            printf("sorry\n");
    }
    return 0;
}