#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n, n) {
        int pos = 0;
        int time = 0;
        while (n--) {
            int next;
            cin >> next;
            if (pos < next) {
                time += 6 * (next - pos);
            } else if (pos > next) {
                time += 4 * (pos - next);
            }
            pos = next;
            time += 5;
        }
        cout << time << endl;
    }

    return 0;
}