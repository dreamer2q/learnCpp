#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, n;
    while (cin >> a >> n) {
        double ret = a;
        double tmp = a;
        for (int i = 1; i < n; i++) {
            tmp = pow(tmp, 1.0 / 2);
            ret += tmp;
        }
        printf("%0.2lf\n", ret);
    }

    return 0;
}
