
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    getchar();
    while (t--) {
        string str;
        getline(cin, str);
        string rstr(str.rbegin(), str.rend());
        cout << rstr << endl;
    }

    return 0;
}