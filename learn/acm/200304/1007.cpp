#include <math.h>
#include <stdio.h>
#include <algorithm>

typedef struct {
    double x, y;
} Pos;

Pos P[100100];

bool cmp(Pos &a, Pos &b) {
    return (a.x + a.y) < (b.x + b.y);
}

#define SQ(x) ((x) * (x))
#define DIS(a, b) sqrt(SQ(a.x - b.x) + SQ(a.y - b.y))

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (0 == n) break;
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &P[i].x, &P[i].y);
        }
        std::sort(P, P + n, cmp);
        double min = 100000000;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < i + 7 && j < n; j++) {
                double d = DIS(P[i], P[j]);
                if (d < min) {
                    min = d;
                }
            }
        }
        printf("%.2lf\n", min / 2);
    }
}