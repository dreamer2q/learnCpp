#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        long long sum = 0, max = 0;
        int c;
        scanf("%d", &c);
        while (c--) {
            int tmp;
            scanf("%d", &tmp);
            sum += tmp;
            if (tmp > max) max = tmp;
        }
        if((sum+1)/2 < max)printf("No\n");
        else printf("Yes\n");
    }

    return 0;
}