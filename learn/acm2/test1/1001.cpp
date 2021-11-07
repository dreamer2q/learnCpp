
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        double perch = a * a;
        double semon = b * c;
        double belinda = d * e * 0.5;

        if (perch > semon && perch > belinda) {
            cout << "Perch" << endl;
        }
        if (semon > perch && semon > belinda) {
            cout << "Semon" << endl;
        }
        if (belinda > perch && belinda > semon) {
            cout << "Belinda" << endl;
        }
    }

    return 0;
}