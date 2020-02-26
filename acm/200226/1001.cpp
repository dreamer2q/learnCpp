#include <stdio.h>

int main(){

    int n;
    while(scanf("%d",&n) == 1 && n){
        int sum=0;
        while(n)sum+=n--;
        printf("%d\n\n",sum);
    }

    return 0;
}