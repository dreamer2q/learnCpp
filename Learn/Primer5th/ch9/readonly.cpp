/*
by dreamer2q
2020年5月13日

只读算法
*/

#include <bits/stdc++.h>

using namespace std;

string b(int i) {
    return i ? "true" : "false";
}

int main() {
    //find,count
    //sum
    int pi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    auto sum = accumulate(begin(pi), end(pi), 0);
    cout << sum << endl;

    //equal
    vector<string> str = {
        "string1",
        "string2",
    };
    const char* pstr[] = {
        "string1",
        "string2",
    };

    //pstr 至少需要和str一样长
    auto res = equal(str.cbegin(), str.cend(), begin(pstr));
    cout << b(res) << endl;

    //accumulate
    vector<double> vd = {
        1,
        2,
        3,
        4,
    };
    cout << accumulate(vd.cbegin(), vd.cend(), 0) << endl;
    return 0;
}