
#include <bits/stdc++.h>

using namespace std;

long long pigs[41] = {0, 1, 1, 5, 9, 29};
long long born[41] = {0, 1, 0, 4, 4, 20};

void initPigs() {
    for (int i = 5; i <= 40; i++) {
        born[i] = (born[i - 2] + born[i - 3] + born[i - 4]) * 4;
        pigs[i] = pigs[i - 1] + born[i] - born[i - 5];
    }
}

int main() {
    initPigs();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << pigs[n] << endl;
    }
    return 0;
}