/*
 * File Created: Wednesday, 24th June 2020 6:30:29 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 24th June 2020 6:36:03 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string type;
        cin >> type;
        int n;
        cin >> n;
        vector<int> data;
        for (int i = 0; i < n; i++) {
            int d;
            cin >> d;
            data.push_back(d);
        }
        if (type == "Faster") {
            cout << *min_element(data.begin(), data.end());
        } else {
            cout << *max_element(data.begin(), data.end());
        }
        cout << endl;
    }
    return 0;
}
