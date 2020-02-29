#include <stdio.h>

int pow(int a, int b, int mod) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans % mod;
}

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) == 2) {
        if (a == 0) break;
        printf("%d\n", pow(a, b, 1000));
    }

    return 0;
}