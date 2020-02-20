#include <stdio.h>

int main(){


    int N;
    scanf("%d",&N);
    for(int c=1;c<=N;c++){
        int n,start,end,max,sum;
        sum=0;
        max = -10001;
        start=end=1;
        int maxstart,maxend;
        maxstart=maxend=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            int tmp;
            scanf("%d",&tmp);
            sum+=tmp;
            if(sum>max){
                max=sum;
                maxstart=start;
                maxend=i;
            }
            if(sum < 0){
                sum=0;
                start=i+1;
            }
        }
        printf("Case %d:\n%d %d %d\n",c,max,maxstart,maxend);
        if(c!=N){
            printf("\n");
        }
    }

    return 0;
}