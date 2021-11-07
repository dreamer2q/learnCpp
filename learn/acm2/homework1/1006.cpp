
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int sum = 0;
        while (n--) {
            int tmp;
            cin >> tmp;
            sum += tmp;
        }
        cout << sum << endl;
    }
    return 0;
}