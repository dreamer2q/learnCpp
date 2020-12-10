#include <iostream>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int stat[1111] = {0};
        for (int i = 0; i <= n; i++) {
            bool Pflag = true;
            for (int m = 1; m <= i; m <<= 1) {
                if (stat[i - m] == -1) {
                    Pflag = false;
                }
            }
            stat[i] = Pflag ? -1 : 1;
        }
        cout << (stat[n] == 1 ? "Kiki" : "Cici") << endl;
    }
    return 0;
}
