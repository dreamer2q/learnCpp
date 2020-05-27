/*
 * Copyright: MIT
 * ----
 * File: pair.cpp
 * File Created: Tuesday, 26th May 2020 11:23:22 am
 * Author: dreamer2q (dreamer22qq@gmail.com)
 * Last Modified: Tuesday, 26th May 2020 11:23:25 am
 * Modified By: dreamer2q (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * pair 类型
 *  一个pair保存两个变量，适用于多返回值，map的键值对
 */

#include <bits/stdc++.h>
using namespace std;

pair<vector<string>::iterator, size_t> process(vector<string> &v) {
    if (!v.empty()) {
        return make_pair(v.end(), v.size());
    }
    return pair<vector<string>::iterator, size_t>();
}


int main() {
    pair<string, int> p1{
        "string",
        1,
    };

    cout << p1.first << "  " << p1.second << endl;

    return 0;
}
