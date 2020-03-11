
#include <stdio.h>

unsigned long long Table[51];

unsigned long long f(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (Table[n] == 0) {
        Table[n] = f(n - 1) + f(n - 2);
    }
    return Table[n];
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        printf("%lld\n", f(n));
    }

    return 0;
}
