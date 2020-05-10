#include <iostream>

using namespace std;

int ST[11110];
void proc(int m, int n) {
    for (int i = 0; i <= m; i++) {
        bool PFlag = true;
        for (int j = 1; j <= n; j++) {
            int t = i - j;
            if (t < 0)
                break;
            if (ST[t] == -1)
                PFlag = false;
        }
        ST[i] = PFlag ? -1 : 1;
    }
}

int main() {
    int cas;
    cin >> cas;
    while (cas--) {
        int m, n;
        cin >> m >> n;
        proc(m, n);
        cout << (ST[m] == 1 ? "Grass" : "Rabbit") << endl;
    }
    return 0;
}