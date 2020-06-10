/*
 * File Created: Tuesday, 2nd June 2020 10:31:04 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 2nd June 2020 11:05:32 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

map<string, string> build_map(ifstream& map_file) {
    map<string, string> trans_map;
    string key, value;
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() > 1) {
            trans_map.insert({key, value.substr(1)});
        } else {
            throw runtime_error("no rule for" + key);
        }
    }
    return trans_map;
}

const string& transform(const string& s, const map<string, string>& m) {
    auto map_it = m.find(s);
    if (map_it != m.end()) {
        return map_it->second;
    }
    return s;
}

void word_transform(ifstream& map_file, istream& input) {
    auto trans_map = build_map(map_file);
    string text;
    while (getline(input, text)) {
        istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word) {
            if (firstword) {
                firstword = false;
            } else {
                cout << " ";
            }
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

int main() {
    string map_file;
    ifstream file;
    cout << "input map file:";
    cin >> map_file;
    file.open(map_file, ios::in);
    word_transform(file, cin);
    return 0;
}