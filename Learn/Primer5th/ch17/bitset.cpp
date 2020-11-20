
#include <bits/stdc++.h>

using namespace std;

int main() {
    //# bitset, 提供长二进制数据处理能力
    // 例如 unsigned long long 只有64位， bitset<n> 代表有n个二进制位

    bitset<128> bit_u(~0ULL);
    cout << bit_u.to_string() << endl;
    cout << bit_u.to_string('1', '0') << endl;

    return 0;
}