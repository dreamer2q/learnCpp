#include <math.h>
#include <stdio.h>

double nth(int a, int n) {
    double ans = a;
    double tmp = a;
    while (n-- > 1) {
        ans += (tmp = sqrt(tmp));
    }
    return ans;
}

int main() {
    int a,b;
    while(scanf("%d %d",&a,&b) == 2){
        printf("%.2lf\n",nth(a,b));
    }
}
