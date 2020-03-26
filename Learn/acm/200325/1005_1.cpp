
#include <stdio.h>
#define ll long long

int main() {
    ll a[40 + 5] = {0, 1, 0, 4, 4};
    ll sum[40 + 5] = {0, 1, 1, 5, 9};
    for (int i = 5; i < 45; i++) {
        a[i] = (a[i - 2] + a[i - 3] + a[i - 4]) * 4;
        sum[i] = sum[i - 1] + a[i] - a[i - 5];
    }
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        int x;
        scanf("%d", &x);
        printf("%lld\n", sum[x]);
    }
}