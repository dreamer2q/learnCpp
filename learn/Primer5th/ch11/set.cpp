/*
 * Copyright: MIT
 * ----
 * File: set.cpp
 * File Created: Tuesday, 26th May 2020 11:01:45 am
 * Author: dreamer2q (dreamer22qq@gmail.com)
 * Last Modified: Tuesday, 26th May 2020 11:01:50 am
 * Modified By: dreamer2q (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 使用set
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    //统计单词出现次数
    //并且使用set来保存不计入统计的单词
    map<string, size_t> word_count;
    set<string> exclude = {
        "The", "the", "and", "And", "Or", "or", "An", "A", "an", "a", "but", "But"};

    string word;
    while (cin >> word) {
        if (exclude.find(word) == exclude.end()) {
            ++word_count[word];
        }
    }
    cout << "statistics: " << endl;
    for (auto item : word_count) {
        cout << item.first << " : " << item.second << endl;
    }

    return 0;
}
