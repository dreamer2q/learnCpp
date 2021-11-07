/*
 * File Created: Friday, 12th June 2020 7:05:01 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Friday, 12th June 2020 10:39:52 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

class Int {
public:
    Int(int i) : m(i) {}

    operator long() const {
        return m;
    }
    operator bool() const {
        return false;
    }

private:
    int m;
};

int main() {
    Int i(10);
    if (i) {
        cout << "i is true" << endl;
    } else {
        cout << "i is false" << endl;
    }

    return 0;
}