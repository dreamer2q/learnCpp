#include <stdio.h>
#include <algorithm>

/**
 * Time Limit Exceeded 
 */

typedef struct {
    int weight, speed;
    int seq;
} Item;

bool cmp(const Item& a, const Item& b) {
    if (a.speed != b.speed) return a.speed > b.speed;
    return a.weight < b.weight;
}

Item M[1001];

typedef struct {
    Item* s[1001];
} PROC;

PROC seq;
PROC res;
int max = 0;
int _index = 0;

void check(int start, int n) {
    seq.s[_index] = M + start;
    for (int i = start + 1; i < n; i++) {
        if (seq.s[_index]->weight < M[i].weight) {
            _index++;
            check(i, n);
            if (_index > max) {
                max = _index;
                res = seq;
            }
            _index--;
        }
    }
}

int main() {
    int n = 0;
    while (scanf("%d %d", &M[n].weight, &M[n].speed) == 2) {
        M[n].seq = n + 1;
        n++;
    }
    std::sort(M, M + n, cmp);

    check(1, n);

    printf("%d\n", max + 1);
    for (int i = 0; i <= max; i++) {
        printf("%d\n", res.s[i]->seq);
    }
}
