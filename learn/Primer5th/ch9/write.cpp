/*
by dreamer2q
2020年5月13日

写容器算法
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> vs(10, string(10, 'c'));
    //fill
    fill(vs.begin(), vs.end(), string("6"));
    cout << "vector<string>: ";
    for (const auto& s : vs) {
        cout << s << " ";
    }
    cout << endl;

    //插入迭代器
    vector<int> vi;
    auto iter = back_inserter(vi);
    fill_n(iter, 10, 11);
    for (auto i : vi) {
        cout << i << " ";
    }
    cout << endl;

    //重排容器算法
    const char* p = "the quick red fox jumps over the slow red turtle";
    stringstream str(p);
    string word;
    vector<string> vw;
    while (str >> word) {
        vw.push_back(word);
    }
    //去重
    {
        sort(vw.begin(), vw.end());
        auto end_u = unique(vw.begin(), vw.end());
        vw.erase(end_u, vw.end());
    }
    for (const auto& w : vw) {
        cout << w << " ";
    }
    cout << endl;

    //定制操作
    {
        
    }
    return 0;
}