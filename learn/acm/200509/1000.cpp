#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    while (n--) {
        int n, m;
        cin >> n >> m;
        int stat[1111] = {0};
        for (int i = 0; i <= n; i++) {
            bool Pflag = true;
            for (int j = 1; j <= m; j++) {
                if (i - j < 0) {
                    break;
                }
                if (stat[i - j] == -1) {
                    Pflag = false;
                    break;
                }
            }
            stat[i] = Pflag ? -1 : 1;
        }
        cout << (stat[n] == 1 ? "first" : "second") << endl;
    }
    return 0;
}