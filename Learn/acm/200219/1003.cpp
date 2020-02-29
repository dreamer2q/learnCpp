


#include <stdio.h>

int main(){

    int a,b;
    while (scanf("%d %d",&a,&b) == 2){
        int c = a + b;
        if (c) {
            printf("%d\n",c);
        }else
            break;
        
    }

    return 0;
}
