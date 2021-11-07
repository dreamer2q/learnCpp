#include <stdio.h>
#include <algorithm>

/*
    fighting for HDU
*/
int HDU[101];
int JAP[101];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (0 == n) break;
        for (int i = 0; i < n; i++) {
            scanf("%d", HDU + i);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", JAP + i);
        }
        std::sort(HDU, HDU + n);
        std::sort(JAP, JAP + n);
        int s1 = 0, s2 = 0;
        for (int i = 0; i < n; i++) {
            if (HDU[i] > JAP[i]) {
                s1 += 2;
            } else if (HDU[i] == JAP[i]) {
                s1 += 1;
                s2 += 1;
            } else {
                s2 += 2;
            }
        }
        printf("%d vs %d\n", s1, s2);
    }
}