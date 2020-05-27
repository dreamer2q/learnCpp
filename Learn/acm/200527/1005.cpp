#include <bits/stdc++.h>

using namespace std;

int main() {
    const string end = "#";
    string line;
    while (getline(cin, line)) {
        if (line == end) {
            break;
        }
        set<string> m;
        string word;
        stringstream str(line);
        while (str >> word) {
            m.insert(word);
        }
        cout << m.size() << endl;
    }
    return 0;
}