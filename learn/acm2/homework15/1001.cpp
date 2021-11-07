/*
hash
*/

#include <bits/stdc++.h>

using namespace std;

const int NOTFOUND = -1;

const int HASH_SIZE = 15123;
int HASH_SET[HASH_SIZE];
int HASH_KEY[HASH_SIZE];

void init_hash() {
    memset(HASH_KEY, NOTFOUND, sizeof(HASH_SET));
    memset(HASH_SET, 0, sizeof(HASH_SET));
}

int hash_func(int key) {
    return abs(key % HASH_SIZE);
}

int& hash_set(int key) {
    int k = hash_func(key);
    while (HASH_KEY[k] != NOTFOUND && HASH_KEY[k] != key) k = (k + 1) % HASH_SIZE;
    HASH_KEY[k] = key;
    return HASH_SET[k];
}

int hash_get(int key) {
    int k = hash_func(key);
    while (HASH_KEY[k] != NOTFOUND && HASH_KEY[k] != key) k = (k + 1) % HASH_SIZE;
    return HASH_SET[k];
}

int main() {
    int n;
    while (cin >> n) {
        init_hash();
        int t, ans = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &t);
            hash_set(t)++;
            if (hash_get(t) > ans) {
                ans = hash_get(t);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
