#include <stdio.h>

int power(int a, int b, int mod) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans % mod;
}

int a[] = {
    0,
    1,
    4,
    7,
    6,
    5,
    6,
    3,
    6,
    9,
    0,
    1,
    6,
    3,
    6,
    5,
    6,
    7,
    4,
    9,
};

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int i;
        scanf("%d", &i);
        printf("%d\n", a[i % 20]);
    }

    return 0;
}