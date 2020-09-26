/*
 * File Created: Thursday, 11th June 2020 11:36:57 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Friday, 12th June 2020 5:36:51 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

default_random_engine randEngine(time(nullptr));
int myRand() {
    uniform_int_distribution<> randDis(0, 9);
    return randDis(randEngine);
}

long long myPow(int x, int y) {
    long long ans = 1;
    while (y--) {
        ans *= x;
    }
    return ans;
}

void testMyPow() {
    cout << myPow(1, 2) << endl;
    cout << myPow(2, 1) << endl;
    cout << myPow(2, 3) << endl;
}

using placeholders::_1;

int main() {
    vector<int> vec(10);
    generate(vec.begin(), vec.end(), myRand);

    //original random sequence
    ostream_iterator<int> out_iter(cout, " ");
    copy(vec.begin(), vec.end(), out_iter);
    cout << endl;
    //5^n
    transform(vec.begin(), vec.end(), out_iter, bind(myPow, 5, _1));
    cout << endl;
    //n^7
    transform(vec.begin(), vec.end(), out_iter, bind(myPow, _1, 7));
    cout << endl;
    //n^n
    transform(vec.begin(), vec.end(), out_iter, bind(myPow, _1, _1));
    cout << endl;
    return 0;
}