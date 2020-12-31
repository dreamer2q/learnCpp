/*
sort 
*/

#include <bits/stdc++.h>

using namespace std;

// const int NOTFOUND = 11111111;

// const int HASH_SIZE = 525123;
// int HASH_SET[HASH_SIZE];
// int HASH_KEY[HASH_SIZE];

// void init_hash() {
//     for (int i = 0; i < HASH_SIZE; i++) {
//         HASH_KEY[i] = NOTFOUND;
//     }
// }

// int hash_func(int key) {
//     return abs(key % HASH_SIZE);
// }

// void hash_set(int key) {
//     int k = hash_func(key);
//     while (HASH_KEY[k] != NOTFOUND) k = (k + 1) % HASH_SIZE;
//     HASH_SET[k] = key;
//     HASH_KEY[k] = key;
// }

// bool hash_exist(int key) {
//     int k = hash_func(key);
//     while (HASH_KEY[k] != NOTFOUND && HASH_KEY[k] != key) k = (k + 1) % HASH_SIZE;
//     return HASH_KEY[k] == key;
// }

// int hash_get(int key) {
//     int k = hash_func(key);
//     while (HASH_KEY[k] != NOTFOUND) k = (k + 1) % HASH_SIZE;
//     return HASH_SET[k];
// }

char _hash[1100000];

const int offset = 500000;

int main() {
    int n, m;
    while (cin >> n >> m) {
        int t;
        for (int i = 0; i < n; i++) {
            scanf("%d", &t);
            _hash[t + offset] = 1;
        }
        for (int i = 1000000; i >= 0; i--) {
            if (_hash[i]) {
                printf("%d", i - offset);
                if (--m == 0) break;
                putchar(' ');
            }
        }
        putchar(10);
        memset(_hash, 0, sizeof(_hash));
    }
    return 0;
}
