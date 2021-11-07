#include <stdio.h>
#include <algorithm>

/*

HDUOJ 1052

是非常经典的贪心问题，只是这个最优策略并不像故事中那么简单。

首先，将两人的马 降序 排列。 分别用两个头指针两个尾指针，方便进行操作。

（1）如果 田忌 最快的马 比 对手最快的马快，直接比，赢一场，两个头指针加加。

（2）如果 田忌 最快的马 比 对手最快的马慢，那肯定是要输一场的，就拿田忌最慢的马

去和对手最快的马比。

（3）如果两人最快的马的速度相同，先不要着急去打平局。此时再看最慢的马。

                <1>如果最慢的马比对手最慢的马快，直接比，赢一场。
                <2>如果最慢的马比对手最慢的马慢，这个最慢的马肯定要输一场，和对手最快的马去比赛。
                这样同样是输，又消耗了对手一个最快的马。
                <3>如果两人最慢的马的速度也相同，，也拿最慢的和对手最快的比较，此时要注意的是
                 会不会两人的马的速度都相同。

*/

bool cmp(int a, int b) {
    return a > b;
}

int main() {
    int King[1001], Ji[1001];
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            scanf("%d", Ji + i);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", King + i);
        }
        std::sort(King, King + n, cmp);
        std::sort(Ji, Ji + n, cmp);
        int win = 0;
        int ks = 0, ke = n - 1;
        int js = 0, je = n - 1;
        while (ks <= ke && js <= je) {
            if (Ji[js] > King[ks]) {
                win++;
                js++;
                ks++;
            } else if (Ji[js] < King[ke]) {
                win--;
                je--;
                ks++;
            } else {
                if (Ji[je] > King[ke]) {
                    win++;
                    je--;
                    ke--;
                } else if (
                    Ji[je] < King[ke]) {
                    win--;
                    je--;
                    ks++;
                } else {
                    if (Ji[je] < King[ks])
                        win--;
                    je--;
                    ks++;
                }
            }
        }

        printf("%d\n", win * 200);
    }

    return 0;
}