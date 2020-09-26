/*
 * File Created: Tuesday, 23rd June 2020 10:05:31 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 23rd June 2020 12:05:31 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

class B {
public:
    virtual void Show() const { cout << "B"; }  // 输出信息
};
class D : public B {
public:
    void Show() const { cout << "D"; }  // 输出信息
};
void Fun1(const B *p) { p->Show(); }     // 定义Fun1()
void Fun2(const B &obj) { obj.Show(); }  // 定义Fun2()
void Fun3(const B obj) { obj.Show(); }   // 定义Fun3()
int main()                               // 主函数main()
{
    B *p = new D;  // 指针
    D d;           // 对象
    Fun1(p);       // 调用Fun1()
    Fun2(d);       // 调用Fun2()
    Fun3(d);       // 调用Fun3()
    cout << endl;  // 换行
    return 0;      // 返回值0, 返回操作系统
}
