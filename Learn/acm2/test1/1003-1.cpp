
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        getchar();
        char org[55] = {0};
        char re[55] = {0};
        scanf("%[^\n]", org);
        int len = strlen(org);
        for (int i = 0; i < len; i++) {
            re[i] = org[len - i - 1];
        }
        cout << re << endl;
    }
}