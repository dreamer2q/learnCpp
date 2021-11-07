


#include <stdio.h>

int main(){

    int N;
    while(scanf("%d",&N) != EOF){
        int sum = 0;
        do{
            sum += N;
        }while(--N);
        printf("%d\n\n",sum);
    }

    return 0;
}
