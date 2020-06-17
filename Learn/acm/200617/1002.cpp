/*
 * File Created: Wednesday, 17th June 2020 6:55:18 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 17th June 2020 7:04:53 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string line;
        cin >> line;
        stringstream ss(line);
        char c;
        unsigned int ans = 0;
        while (ss >> c) {
            if (isdigit(c)) {
                ans *= 10;
                ans += c - '0';
            }
        }
        cout << ans * 513 << endl;
    }
    return 0;
}