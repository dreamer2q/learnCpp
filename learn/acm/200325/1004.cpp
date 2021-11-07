#include <cmath>
#include <iostream>

using namespace std;

int main() {
    long long n;
    while (scanf("%lld", &n) == 1) {
        if (0 == n) break;

        int s = 1;
        for (int i = 2; i * i <= n; i++) {
            int r = 0;
            while (n % i == 0) {
                r++;
                n /= i;
            }
            if (r > 0) {
                r++;
                s *= r;
            }
        }
        if (n > 1)
            s *= 2;

        printf("%d\n", s);
    }
    return 0;
}