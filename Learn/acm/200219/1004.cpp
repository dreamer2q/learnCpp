

#include <stdio.h>

int main(){

    int N;
    while(scanf("%d",&N) && N){
        int sum = 0;
        for(int i=0;i<N;i++){
            int t;
            scanf("%d",&t);
            sum += t;
        }
        printf("%d\n",sum);
    }

    return 0;
}
