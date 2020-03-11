

#include <stdio.h>

unsigned long long Table[51];

unsigned long long f(int n) {
    if (n == 1) return 1;
    if (n == 2) return 1;
    if (Table[n] == 0) {
        Table[n] = f(n - 1) + f(n - 2);
    }
    return Table[n];
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
