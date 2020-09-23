#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int count, sum = 0;
        cin >> count;
        while (count--) {
            int tmp;
            cin >> tmp;
            sum += tmp;
        }
        cout << sum << endl;
    }
    return 0;
}