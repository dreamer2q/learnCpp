/*
 * File Created: Monday, 22nd June 2020 4:40:12 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Monday, 22nd June 2020 4:57:34 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

string replace(string line, string o, string n) {
    auto i = line.find(o);
    if (i != string::npos) {
        return line.replace(i, o.length(), n);
    }
    return line;
}

int main() {
    string line;
    cout << "> ";
    while (getline(cin, line)) {
        line = replace(line, "Äã", "ÎÒ");
        line = replace(line, "Âğ", "");
        line = replace(line, "?", "");
        line = replace(line, "£¿", "");
        cout << line << endl;
        cout << "> ";
    }
}
