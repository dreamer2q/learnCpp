#include <bits/stdc++.h>

using namespace std;

int main() {
    string line;

    while (getline(cin, line)) {
        map<char, int> m;
        for (int i = 'a'; i <= 'z'; i++) {
            m[i] = 0;
        }
        for (const char& c : line) {
            if (isalpha(c)) {
                m[c]++;
            }
        }
        for (const auto& e : m) {
            cout << e.first << ":" << e.second << endl;
        }
        cout << endl;
    }

    return 0;
}