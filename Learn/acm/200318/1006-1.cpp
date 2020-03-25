
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

typedef struct
{
    int w, s, pos;
} Fatmouse;

typedef struct
{
    int pre, num;
} s;

bool cmp(Fatmouse a, Fatmouse b) {
    if (a.w == b.w) {
        return a.s > b.s;
    }
    return a.w < b.w;
}

int main(int argc, char *argv[]) {
    Fatmouse a[1001];
    s dp[1001];
    int i, j, k, max1;
    i = 0;
    while (cin >> a[i].w >> a[i].s) {
        a[i].pos = i + 1;
        i++;
    }
    sort(a, a + i, cmp);
   
    for (j = 0; j < i; j++) {
        dp[j].pre = 0;
        dp[j].num = 1;
    }

    for (j = 0; j < i; j++) {
        max1 = 0;
        for (k = 0; k < j; k++) {
            if (a[k].s > a[j].s && a[k].w < a[j].w) {
                if (dp[k].num > max1) {
                    max1 = dp[k].num;
                    dp[j].pre = k;
                }
            }
        }
        dp[j].num = max1 + 1;
    }
    max1 = 0;
    int t = 0;
    for (j = 0; j < i; j++) {
        if (dp[j].num > max1) {
            max1 = dp[j].num;
            t = j;
        }
    }
    cout << max1 << endl;
    int xh[10000];
    for (j = 0; j < max1; j++) {
        xh[j] = t;
        t = dp[t].pre;
    }

    for (j = max1 - 1; j >= 0; j--) {
        cout << a[xh[j]].pos << endl;
    }
    return 0;
}
