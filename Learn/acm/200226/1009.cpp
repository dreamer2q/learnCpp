#include <stdio.h>

int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {

    int a, b;
    while (scanf("%d %d", &a, &b) == 2) {
        printf("%d\n", a / gcd(a, b) * b);
    }

    return 0;
}