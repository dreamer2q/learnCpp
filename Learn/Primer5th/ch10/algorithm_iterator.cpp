/*
 * Copyright: MIT
 * ----
 * File: algorithm_iterator.cpp
 * File Created: Tuesday, 26th May 2020 10:16:01 am
 * Author: dreamer2q (dreamer22qq@gmail.com)
 * Last Modified: Tuesday, 26th May 2020 10:30:03 am
 * Modified By: dreamer2q (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 泛型算法
 */

/*
5类迭代器

 - input iterator
 *it++ 保证有效
 单边扫描算法

 - output iterator
只能向输出迭代器赋值一次，单边扫描

 - forward iterator
多次读写，但是只能向一个方向移动

 - bidirectional iterator
类似单向迭代器，可以双向

 - random access iterator
 常量时间内访问序列中的任意元素


 算法的形参模式

 alg(beg, end, args);
 alg(beg, end, dest, args);
 alg(beg, end, beg2, args);
 alg(beg, emd, beg2, end2, args);

 主要以接送迭代器为主
 但是也有一些小区别

 - 接受额外的谓词参数的重载版本
 - _if 版本
 - 区分拷贝 _copy 

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    //TODO
    return 0;
}