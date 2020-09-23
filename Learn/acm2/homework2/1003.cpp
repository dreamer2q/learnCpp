
#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    int t = a % b;
    while (t) {
        a = b;
        b = t;
        t = a % b;
    }
    return b;
}

int lcm(long long a, long long b) {
    return a * b / gcd(a, b);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ret, a;
        cin >> ret;
        while (--n) {
            cin >> a;
            ret = lcm(ret, a);
        }
        cout << ret << endl;
    }
    return 0;
}
