
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int c;
        cin >> c;
        int sum = 0;
        while (c--) {
            int tmp;
            cin >> tmp;
            sum += tmp;
        }
        cout << sum << endl
             << endl;
    }
    return 0;
}