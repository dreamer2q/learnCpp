#include <stdio.h>

int f(int n) {
    if (n == 0) return 7;
    if (n == 1) return 11;
    return f(n - 1) + f(n - 2);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (n > 8) n %= 8;
        if (n == 2 || n == 6)
            printf("yes\n");
        else
            printf("no\n");
    }

    return 0;
}