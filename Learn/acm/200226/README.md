# intro

202002《ACM程序设计》作业（2）—— 刘春英老师

[link](http://acm.hdu.edu.cn/webcontest/contest_show.php?cid=13650)

# 要点

## 快速幂

```Cpp
int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1) ans=(ans*a) % mod;
        a = (a*a) % mod;
        b >>= 1;
    }
    return ans % mod;
}
```

## 对于有限可能结果的处理

这种常见于结果需要`mod`的题目，且题目给出的数很大

常见思路：
    打表，确定循环的范围



