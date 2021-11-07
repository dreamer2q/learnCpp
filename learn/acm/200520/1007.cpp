#include <bits/stdc++.h>

using namespace std;

#define NMAX 10010

int c1[NMAX];
int c2[NMAX];

int main() {
    int n;
    while (cin >> n) {
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int s;
            cin >> s;
            sum += s;
            if (i == 0) {
                c1[0] = 1;
                c1[s] = 1;
            } else {
                for (int j = 0; j <= sum; j++) {
                    for (int k = 0; k + j <= sum && k <= s; k += s) {
                        c2[j + k] += c1[j];
                        c2[abs(j - k)] += c1[j];
                    }
                }
                memcpy(c1, c2, sizeof(c2));
                memset(c2, 0, sizeof(c2));
            }
        }
        vector<int> no;
        for (int i = 1; i <= sum; i++) {
            if (!c1[i]) {
                no.push_back(i);
            }
        }
        cout << no.size() << endl;
        for (int i = 0; i < no.size(); i++) {
            cout << no[i];
            if (i != no.size() - 1) {
                cout << " ";
            }
        }
        if (!no.empty())
            cout << endl;
    }
    return 0;
}