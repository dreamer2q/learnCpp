
#include <stdio.h>

unsigned long long table[50];

unsigned long long f(int n) {
    if (n == 1) return 3;
    if (n == 2) return 7;
    if (table[n] == 0) {
        table[n] = 2 * f(n - 1) + f(n - 2);
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