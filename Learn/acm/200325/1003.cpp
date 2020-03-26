#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

bool check(int n) {
    if (n <= 7) return true;
    bool flag = false;

    if (n % 2 == 0)
        return check(n / 2);

    if (n % 3 == 0)
        return check(n / 3);
    if (n % 5 == 0)
        return check(n / 5);
    if (n % 7 == 0)
        return check(n / 7);
    return false;
}

int main() {
    int n;
    cin >> n;
    int m;
    while (cin >> m) {
        cout << (check(m) ? "Yes" : "No") << endl;
    }
    return 0;
}