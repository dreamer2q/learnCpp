

#include <stdio.h>

int f(int n) {
    return 2 * n * n - n + 1;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int a;
        scanf("%d", &a);
        printf("%d\n", f(a));
    }
    return 0;
}