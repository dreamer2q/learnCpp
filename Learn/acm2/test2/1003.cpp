#include <bits/stdc++.h>
using namespace std;

#define po(x) ((x) * (x))

int main() {
    int t;
    cin >> t;
    while (t--) {
        int sides[3];
        scanf("%d%d%d", &sides[0], &sides[1], &sides[2]);
        sort(sides, sides + 3);
        int a = sides[0];
        int b = sides[1];
        int c = sides[2];
        if (!(a + b > c && a + c > b && b + c > a)) {
            cout << "Impossible!" << endl;
            continue;
        }
        int A = po(c);
        int B = po(a) + po(b);
        // int C = po(c);
        if (A == B) {
            cout << "Right triangle" << endl;
        } else if (A < B) {
            cout << "Acute triangle" << endl;
        } else {
            cout << "Obtuse triangle" << endl;
        }
    }
    return 0;
}