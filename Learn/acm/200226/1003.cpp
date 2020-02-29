#include <stdio.h>

int gcd(int a, int b) {
    int tmp;
    while (b) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int c;
        scanf("%d", &c);
        int a, b;
        scanf("%d", &a);
        for (int i = 1; i < c; i++) {
            scanf("%d", &b);
            a = a / gcd(a, b) * b;
        }
        printf("%d\n", a);
    }

    return 0;
}