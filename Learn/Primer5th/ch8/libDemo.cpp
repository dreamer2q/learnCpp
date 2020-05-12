#include <bits/stdc++.h>

using namespace std;

int main() {
    list<const char*> ls = {
        "dreamer2q",
        "myjj",
    };

    vector<string> vs;

    vs.assign(ls.begin(), ls.end());

    for (const auto& e : vs) {
        cout << e << endl;
    }

    vector<int> v1 = {
        1,
        2,
        3,
        4,
        5,
    };
    vector<int> v2 = {
        1,
        2,
        3,
        4,
        9,
    };

    cout << (v1 > v2) << endl;

    return 0;
}