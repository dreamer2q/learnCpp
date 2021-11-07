#include <bits/stdc++.h>

using namespace std;

template <typename T>
void out(const vector<T>& o, const string& prefix = "") {
    cout << prefix << ": ";
    for_each(o.begin(), o.end(), [](const T& item) {
        cout << item << " ";
    });
    cout << endl;
}

// 再探迭代器
int main() {
    //# 插入迭代器
    vector<int> container;
    auto front_iter = inserter(container, container.begin());
    for (int i = 0; i < 10; i++) {
        front_iter = i;
    }
    out(container, "front_iter");
    auto back_iter = inserter(container, container.end());
    for (int i = 10; i >= 0; i--) {
        back_iter = -i;
    }
    out(container, "back_iter");
    auto push_iter = back_inserter(container);

    //# iostream 迭代器
    //## istream_iterator, 读取输入流
    istream_iterator<int> int_eof;  //尾后迭代器
    ifstream in("in.txt");
    istream_iterator<int> int_is(in);           //从in读取int
    vector<int> int_iter_vec(int_is, int_eof);  //从迭代器范围构造vector
    out(int_iter_vec, "int_iter_vec");

    //## ostream_iterator, 输入数据到流
    ostream_iterator<int> int_out(cout, " ");  //输出到控制台，使用 " " 作为分隔符
    copy(int_iter_vec.begin(), int_iter_vec.end(), int_out);
    cout << endl;
    //## 迭代器处理类类型数据
    //这个要求你的类实现<<,>>的运算符

    //# 反向迭代器
    reverse_copy(container.begin(), container.end(), int_out);
    cout << endl;
    return 0;
}
