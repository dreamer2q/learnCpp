/*
 * Copyright: MIT
 * ----
 * File: map_insert.cpp
 * File Created: Tuesday, 26th May 2020 11:50:13 am
 * Author: dreamer2q (dreamer22qq@gmail.com)
 * Last Modified: Tuesday, 2nd June 2020 10:51:42 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    map<string, int> m;

    m.insert({"shit", 1000});
    m.insert(make_pair("fuck", 2000));
    m.insert(pair<string, int>("what", 10));
    m.insert(map<string, int>::value_type("gogo", 0));

    cout << "map<string,int> = {" << endl;
    auto beg = m.begin();
    while (beg != m.end()) {
        cout << " " << beg->first << " : " << beg->second << " ," << endl;
        beg++;
    }
    cout << "}" << endl;

    if (m.find("shift") == m.end()) {
        cout << "shift is not in map" << endl;
    }

    multimap<string, string> authors = {
        {"dreamer", "book1"},
        {"dreamer", "book2"},
        {"dreamer", "book3"},
        {"dreamer", "book4"},
        {"dreamer", "book5"},
        {"dreamer", "book6"},
        {"dreamer", "book7"},
        {"dreamer2q", "none"},
    };

    auto entries = authors.count("dreamer");
    auto iter = authors.find("dreamer");
    cout << "dreamer: ";
    while (entries) {
        cout << iter->second << " ";
        iter++;
        entries--;
    }
    cout << endl;

    //使用迭代器的解决方案
    cout << "using iterator : " << endl;
    for (auto beg = authors.lower_bound("dreamer"),
              end = authors.upper_bound("dreamer");
         end != beg; ++beg) {
        cout << beg->second << endl;
    }

    //迭代器方案2，equal_range 函数-> pair<low,upp>
    cout << "equal_range iterator method" << endl;
    for (auto pos = authors.equal_range("dreamer"); pos.first != pos.second; pos.first++) {
        cout << pos.first->second << endl;
    }

        return 0;
}