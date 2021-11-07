#include <stdio.h>

unsigned long long table[60];

unsigned long long f(int n) {
    if (n <= 4) return n;
    if (table[n] == 0) {
        table[n] = f(n - 1) + f(n - 3);
    }
    return table[n];
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        printf("%lld\n", f(n));
    }
    return 0;
}