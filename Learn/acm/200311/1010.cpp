
#include <stdio.h>

#define ULL unsigned long long

ULL table[40] = {1, 1};

int main() {
    for (int i = 2; i <= 35; i++)
        for (int j = 0; j <= i; j++) {
            table[i] += table[j] * table[i - j - 1];
        }
    int counter = 1;
    int n;
    while (scanf("%d", &n) == 1 && n != -1) {
        printf("%d %d %lld\n", counter++, n, table[n] * 2);
    }

    return 0;
}