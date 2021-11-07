#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> vs = {
        "vector string",
        "str",
        "single",
        "bachelor",
        "student",
        "single",
    };

    cout << count(vs.begin(), vs.end(), "single") << endl;

    auto res = find(vs.begin(), vs.end(), "single");
    if (res == vs.end()) {
        cout << "not found" << endl;
    }
    cout << *res << endl;

    return 0;
}