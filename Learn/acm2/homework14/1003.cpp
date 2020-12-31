/*

HDU 1171 Big Event in HDU

这题可以使用01背包解决

但是为了学习母函数就用母函数解决

解题还是要明白算法的思路，改开数组的时候就不用搞vector

*/

#include <bits/stdc++.h>

using namespace std;

int c1[250000];
int c2[250000];

int main() {
    int value[60] = {0};
    int count[110] = {0};

    int n;
    while (cin >> n && n > 0) {
        int v, c;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> value[i] >> count[i];
            sum += value[i] * count[i];
        }

        for (int i = 0; i <= sum; i++) {
            c1[i] = 0;
            c2[i] = 0;
        }

        //初始化的第一项比较重要, 也就是第一个括号里面的内容
        for (int i = 0; i <= count[0] * value[0]; i += value[0]) {
            c1[i] = 1;
        }
        //接下来就是从第二个括号开始计算
        for (int i = 1; i < n; i++) {
            //j代表每一项的系数
            for (int j = 0; j <= sum; j++) {
                //将j代表的系数，与下一项的每一个系数进行相乘(+)
                for (int k = 0; k <= value[i] * count[i] && k + j <= sum; k += value[i]) {
                    c2[j + k] += c1[j];
                }
            }
            for (int j = 0; j <= sum; j++) {
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }

        for (int i = sum / 2; i >= 0; i--) {
            if (c1[i]) {
                cout << sum - i << " " << i << endl;
                break;
            }
        }
    }

    return 0;
}
