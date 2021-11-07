
#include <stdio.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))

#define SEC_V ((6.0))
#define MIN_V ((1.0/10))
#define HOU_V ((1.0/120))

double DD;

typedef struct{
    double left;
    double right;
} INTERVAL;

INTERVAL solve(double v,double c){
    INTERVAL p;
    if(v>0){
        p.right = (360-DD-c)/v;
        p.left = (DD-c)/v;
    }else{
        p.left = (360-DD-c)/v;
        p.right = (DD-c)/v;
    }
    if(p.left<0)p.left =0;
    if(p.right>60)p.right=60;
    if(p.right<=p.left)p.left=p.right=0;
    return p;
}

INTERVAL AND(INTERVAL a,INTERVAL b){
    INTERVAL r;
    r.left = max(a.left,b.left);
    r.right = min(a.right,b.right);
    if(r.left>=r.right)r.left=r.right=0;
    return r;
}

double happy(int hour,int minute){
    double Dh = hour*30 + minute*1.0/2.0;
    double Dm = minute*6;
    double vdiff;
    double adiff;

    INTERVAL v[3][2];
    vdiff = MIN_V-HOU_V;
    adiff = Dm-Dh;
    v[0][0] = solve(vdiff,adiff);
    v[0][1] = solve(-vdiff,-adiff);

    vdiff = SEC_V-MIN_V;
    adiff = -Dm;
    v[1][0] = solve(vdiff,adiff);
    v[1][1] = solve(-vdiff,-adiff);

    vdiff = SEC_V - HOU_V;
    adiff = -Dh;
    v[2][0] = solve(vdiff,adiff);
    v[2][1] = solve(-vdiff,-adiff);

    double res=0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                INTERVAL tmp = AND(AND(v[0][i],v[1][j]),v[2][k]);
                res += tmp.right - tmp.left;
            }
        }
    }
    return res;
}

int main(){
    
    while(scanf("%lf",&DD) == 1){
        if(DD < 0) break;
        double t = 0;
        for(int h=0;h<12;h++)
            for(int m=0;m<60;m++){
                double tmp = happy(h,m);
                t += tmp;
            }
        printf("%.3lf\n",t*100/43200);
    }

    return 0;
}
