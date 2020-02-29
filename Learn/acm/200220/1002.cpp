#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

#define N 1102


char *add(char* a,char* b){
    int i,j,k,flag;
    static char sum[N];
    i = strlen(a) - 1;
    j = strlen(b) - 1;
    flag = k = 0;
    for(;i>=0 && j>=0;i--,j--,k++){
        sum[k] = a[i] + b[j] - '0' + flag;
        if (sum[k]>'9'){
            sum[k] -= 10;
            flag = 1;
        }else{
            flag = 0;
        }
    }
    for(int t=MAX(i,j);t>=0;t--,k++){
        if(i>=0){
            sum[k] = a[t] + flag;
        }else{
            sum[k] = b[t] + flag;
        }
        if(sum[k]>'9'){
            sum[k] -= 10;
            flag = 1;
        }else{
            flag = 0;
        }
    }
    if(flag){
        sum[k++] = flag + '0';
    }
    sum[k--] = '\0';
    for(int t=0;t<k;t++,k--){
        char tmp = sum[k];
        sum[k] = sum[t];
        sum[t] = tmp;
    }
    return sum;
} 

int main(){
    char A[N],B[N];
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s %s",A,B);
        //这个case 第一个居然是大写的，md，坑了我很久。
        printf("Case %d:\n",i);
        printf("%s + %s = %s\n",A,B,add(A,B));
        if(i!=n){
            printf("\n");
        }
    }

    return 0;
}