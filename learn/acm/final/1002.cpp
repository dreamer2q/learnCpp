/*
 * File Created: Wednesday, 24th June 2020 6:36:38 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 24th June 2020 6:40:39 pm
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
    while (cin >> n && n) {
        int ans = 1;
        while (!(n & 0x01)) {
            ans <<= 1;
            n >>= 1;
        }
        cout << ans << endl;
    }
    return 0;
}