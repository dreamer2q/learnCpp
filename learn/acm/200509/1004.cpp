#include <iostream>
using namespace std;

void ensure(bool condition, string log) {
    if (!condition) {
        cout << log << endl;
    } else {
        cout << "success" << endl;
    }
}

inline bool bit(int num, int b) {
    return num & (1 << (b - 1));
}
int maxbit(int num) {
    int i = 0;
    while (num > 0) {
        num >>= 1;
        i++;
    }
    return i;
}

void test_maxbit() {
    ensure(maxbit(7) == 3, "maxbit 7");
    ensure(maxbit(0) == 0, "maxbit 0");
    ensure(maxbit(8) == 4, "maxbit 8");
}

int main() {
    int n, M[101];
    while (cin >> n) {
        if (n == 0) break;
        int ans = 0;
        int max = 0;
        for (int i = 0; i < n; i++) {
            cin >> M[i];
            ans ^= M[i];
            if (M[i] > max) max = M[i];
        }
        if (ans != 0) {
            int an = 0;
            for (int i = 0; i < n; i++) {
                ans ^= M[i];
                if (M[i] > ans) an++;
                ans ^= M[i];
            }
            ans = an;
        }
        cout << ans << endl;
    }
    return 0;
}