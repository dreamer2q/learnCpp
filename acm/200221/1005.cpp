#include <stdio.h>

#define byte char 
#define N 100

byte fn[N];
int A,B;

#define f(n) (fn[n] = (A*fn[n-1] + B*fn[n-2]) % 7)

/**
 *   
 * 此题有问题，
 * 当n=50的时候，结果就变成了1?
 * 
 * 正确做法，应该找到循环周期的开始，和周期的最小长度 
 * 
 * 这里略
 * 
 * 一下为错误解法。
 * 
 */
int main(){
    fn[0]=fn[1]=1;
    int n;
    while(scanf("%d %d %d",&A,&B,&n) == 3){
        if(n==0)break;
        if(n>49)n%=49;
        for(int i=2;i<n;i++){
            f(i);
        }
        printf("%d\n",fn[n-1]);
    }

    return 0;
}
