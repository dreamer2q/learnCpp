/*
by dreamer2q

迭代器

 - 插入迭代器 insert iterator
 - 流迭代器 stream iterator
 - 反向迭代器 reverse iterator
 - 移动迭代器 move iterator

2020年5月15日

*/

#include <bits/stdc++.h>

using namespace std;

void print(int c) {
    cout << c << ' ';
}

int main() {
    //插入迭代器，接受一个容器，生成一个迭代器，能实现想给定添加元素
    //操作:
    //  it = t
    //  *it,
    //  ++it, it++
    //种类
    //  back_inserter
    //  front_inserter
    //  inserter
    list<int> lst = {1, 2, 3, 4, 5, 6};
    list<int> lst2, lst3;
    copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
    copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));

    for_each(lst2.begin(), lst2.end(), print);
    cout << endl;
    for_each(lst3.begin(), lst3.end(), print);

    //iostream 迭代器
    //istream_iterator
    istream_iterator<string> str_in(cin), str_eof;
    vector<string> words;
    for (int i = 0; i < 3; i++) {
        words.push_back(*str_in++);
    }
    stable_sort(words.begin(), words.end());
    for_each(words.begin(), words.end(), [](const string& s) {
        cout << s << ' ';
    });

    //ostream_iterator
    ostream_iterator<string> out_iter(cout, " ");
    for (auto w : lst) {
        out_iter = to_string(w);
    }
    cout << endl;

    //反向迭代器

    return 0;
}