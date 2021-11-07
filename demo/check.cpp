/*
 * File Created: Friday, 12th June 2020 9:30:11 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Friday, 12th June 2020 9:41:46 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    //不知道为啥vector访问0元素不会崩溃
    vector<string> vs;
    cout << "..." << endl;
    cout << vs.capacity() << endl;
    cout << vs.size() << endl;
    cout << vs[0] << endl;
    cout << vs.at(0) << endl;
    cout << vs.front() << endl;

    return 0;
}
