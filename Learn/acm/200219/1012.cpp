
#include <stdio.h>

int main(){

    int n;
    while(scanf("%d",&n) != EOF){
        int sum = 1;
        for(int i=0;i<n;i++){
            int t;
            scanf("%d",&t);
            if(t%2){
                sum*=t;
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}

