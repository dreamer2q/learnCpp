/*
 * File Created: Saturday, 30th May 2020 12:22:10 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Saturday, 30th May 2020 12:30:32 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>

using namespace std;

template <typename T>
void bubbleSortReverse(T a[], int n) {
    int i = n - 1;
    while (i > 0) {
        int lastExchangeIndex = 0;
        for (int j = 0; j < i; j++) {
            if (a[j + 1] > a[j]) {
                swap(a[j + 1], a[j]);
                lastExchangeIndex = j;
            }
        }
        i = lastExchangeIndex;
    }
}

int main() {
    int a[] = {3, 2, 4, 6, 7, 10, 1, 0};
    bubbleSortReverse(a, sizeof(a) / sizeof(a[0]));
    return 0;
}