#include <stdio.h>

unsigned long long table[60];

unsigned long long f(int n) {
    if (n == 1) return 1;
    if (n == 2) return 3;
    if (table[n] == 0) {
        table[n] = f(n - 1) + 2 * f(n - 2);
    }
    return table[n];
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int a;
        scanf("%d", &a);
        printf("%lld\n", f(a));
    }
    return 0;
}