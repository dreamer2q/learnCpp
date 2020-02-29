



#include <stdio.h>

int main(){

    int N;
    scanf("%d",&N);
    while(N--){
        int sum = 0;
        int M;
        scanf("%d",&M);
        for(int i=0;i<M;i++){
            int t;
            scanf("%d",&t);
            sum += t;
        }
        printf("%d\n",sum);
    }

    return 0;
}
