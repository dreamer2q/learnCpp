/*
dreamer2q

标准库bind函数

一个通用函数配适器，它接受一个可调用对象，生成一个新的可调用对象来”适应”，原对象的参数列表。

2020年5月15日
*/

#include <bits/stdc++.h>

using namespace std;
using namespace std::placeholders;

bool check_size(const string& s, string::size_type sz) {
    return s.size() >= sz;
}

ostream& print(ostream& os, const string& s, char c) {
    return os << s << c;
}

int main() {
    vector<string> words = {
        "apple", "orange", "banana", "strawberry", "watermelon", "pineapple", "peach", "pear"};
    stable_sort(words.begin(), words.end());

    auto wc = find_if(words.begin(), words.end(),
                      bind(check_size, _1, 5));
    cout << *wc << endl;

    //引用绑定，适用于ostream等不可以拷贝的类型
    for_each(words.begin(), words.end(),
             bind(print, ref(cout), _1, ' '));

    return 0;
}