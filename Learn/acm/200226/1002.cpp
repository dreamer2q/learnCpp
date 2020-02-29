#include <stdio.h>

int main() {

    int n;
    while (scanf("%d", &n) == 1 && n) {
        int f = 0, s = 0;
        for(int i=0;i<n;i++){
            int tmp;
            scanf("%d",&tmp);
            if(tmp>f){
                s+= (tmp-f)*6;
            }else{
                s+= (f-tmp)*4;
            }
            f = tmp;
            s+=5;
        }
        printf("%d\n",s);
    }

    return 0;
}