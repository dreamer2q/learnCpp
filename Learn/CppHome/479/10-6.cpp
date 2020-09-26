/*
 * File Created: Thursday, 11th June 2020 10:48:43 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Thursday, 11th June 2020 11:36:36 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

// template <typename T>
// void swap(T& a, T& b) {
//     auto t = a;
//     a = b;
//     b = t;
// }

template <typename T>
void exchange(
    list<T>& l1, typename list<T>::iterator p1,
    list<T>& l2, typename list<T>::iterator p2) {
    //----
    list<T> tmp(p1, l1.end());
    list<T> tmp2(p2, l2.end());
    l1.erase(p1, l1.end());
    l2.erase(p2, l2.end());
    l1.insert(l1.end(), tmp2.begin(), tmp2.end());
    l2.insert(l2.end(), tmp.begin(), tmp.end());
}

void test() {
    list<int> l1 = {1, 2, 3, 4, 5, 6};
    list<int> l2 = {9, 8, 7, 6, 5, 4, 3};

    auto beg = l1.begin();
    beg++;
    beg++;
    beg++;
    ::exchange(l1, beg, l2, l2.begin());

    list<int> want1 = {1, 2, 3, 9, 8, 7, 6, 5, 4, 3};
    list<int> want2 = {4, 5, 6};
    if (equal(l1.begin(), l1.end(), want1.begin()) &&
        equal(l2.begin(), l2.end(), want2.begin())) {
        cout << "success 测试成功" << endl;
    } else {
        cout << "failure 测试失败" << endl;
    }
}

int main() {
    test();
    return 0;
}
