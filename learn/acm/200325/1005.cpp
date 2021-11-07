#include <iostream>

using namespace std;

long long t[44];

long long f(int n) {
    if (n <= 0) return 0;
    if (n <= 2) return 1;
    if (t[n] == 0) {
        t[n] = 4 * f(n - 2) - 5 * f(n - 5) + f(n - 1);
    }
    return t[n];
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", f(n));
    }

    return 0;
}