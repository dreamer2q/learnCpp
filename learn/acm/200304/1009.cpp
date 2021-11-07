
/*
    悼念512汶川大地震遇难同胞——老人是真饿了
*/

#include <stdio.h>
#include <algorithm>

typedef struct {
    int price;
    int weight;
} Item;

Item R[1001];

bool cmp(Item &a, Item &b) {
    return a.price < b.price;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int budget;
        scanf("%d", &budget);
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &R[i].price, &R[i].weight);
        }
        std::sort(R, R + n, cmp);
        double res = 0;
        for (int i = 0; i < n && budget > 0; i++) {
            if (budget > R[i].price * R[i].weight) {
                res += R[i].weight;
                budget -= R[i].price * R[i].weight;
            } else {
                res += double(budget) / R[i].price;
                budget = 0;
            }
        }
        printf("%.2lf\n", res);
    }
    return 0;
}