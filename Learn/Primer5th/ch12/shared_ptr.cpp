/*
 * File Created: Tuesday, 2nd June 2020 11:30:33 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 2nd June 2020 12:11:05 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    shared_ptr<string> p1;
    //安全的分配，调用make_shared
    p1 = make_shared<string>();  //new a empty string
    if (p1 && p1->empty()) {
        *p1 = "hi";
    }
    //像使用指针一样使用只能指针
    cout << *p1 << endl;

    //make_shared
    shared_ptr<int> p2 = make_shared<int>(1000);
    shared_ptr<string> p3 = make_shared<string>(10, '6');
    auto p4 = make_shared<vector<int>>(10, 666);

    //shared_ptr的拷贝和赋值
    //shared_ptr都有一个关联的计数器，称为引用计数(refrence count)
    //当我们拷贝一个shared_ptr时，计数器都会递增
    //一旦一个计数器到了0，它就会自动释放自己所管理的对象（通过析构函数）

    return 0;
}