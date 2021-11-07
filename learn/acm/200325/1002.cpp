#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    string word;
    while (cin >> word) {
        for (auto& w : word) {
            w = tolower(w);
        }
        cout << word << endl;
    }

    return 0;
}