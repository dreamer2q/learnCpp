#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

int main() {
    int a[1001];

    int cases;
    cin >> cases;
    while (cases--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n, cmp);
        for (int i = 0; i < m; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}