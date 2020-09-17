#include <bits/stdc++.h>

using namespace std;

int main() {
    int x1, x2;
    int y1, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        int dx = x1 - x2;
        int dy = y1 - y2;
        cout.flags(ios::fixed);
        cout.precision(2);
        cout << sqrt(dx * dx + dy * dy) << endl;
    }

    return 0;
}