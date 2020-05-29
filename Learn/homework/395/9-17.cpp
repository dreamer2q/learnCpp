/*
 * File Created: Saturday, 30th May 2020 12:30:51 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Saturday, 30th May 2020 12:41:41 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
using namespace std;

template <typename T, unsigned N>
const T* myfind(const T (&a)[N], const T c) {
    for (const auto& e : a) {
        if (e == c) {
            return &e;
        }
    }
    return std::end(a);
}

int main() {
    const int data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 10};
    auto me = std::end(data1);
    auto r1 = myfind(data1, 10);
    auto r2 = myfind(data1, -1);
    return 0;
}
