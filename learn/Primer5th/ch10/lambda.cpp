/*
 * Copyright: MIT
 * ----
 * File: lambda.cpp
 * File Created: Tuesday, 26th May 2020 9:59:58 am
 * Author: dreamer2q (dreamer22qq@gmail.com)
 * Last Modified: Tuesday, 26th May 2020 10:29:16 am
 * Modified By: dreamer2q (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
lambda函数的使用

一些算法可以接收一个额外的谓词，但是对谓词的传入的参收有要求
而有时候我们需要自定义某些参收，这些参收不符合算法对谓词的要求，这个时候lambda就排上用场了。
*/

/*

定义形式

[capture list] (parameter list) -> return type { function body }
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    //不带参数，省略参数列表和返回类型
    auto f = [] { return 42; };
    cout << f() << endl;

    //携带参数
    auto shorter = [](const string& a, const string& b) { return a.size() < b.size(); };
    cout << shorter("123", "123123123") << endl;

    //作为参数传递给一个函数
    vector<string> words = {
        "apple", "orange", "banana", "strawberry", "watermelon", "pineapple", "peach", "pear"};
    stable_sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.size() < b.size();
    });
    {
        cout << "vector<string> words = {" << endl;
        for (auto w : words) {
            cout << w << "," << endl;
        }
        cout << "}" << endl;
    }

    //使用捕获列表
    auto sz = 9;
    auto res = find_if(words.begin(), words.end(), [sz](const string& a) {
        return a.size() > sz;
    });
    if (res == words.end()) {
        cout << "not found" << endl;
    } else {
        cout << *res << endl;
    }

    for_each(words.begin(), words.end(), [](const string& s) {
        cout << s << ", ";
    });
    cout << endl;

    //隐式捕获
    //值捕获,类型比较支持拷贝才可，ostream就不支持，不可以
    [=] {
        for (auto w : words) {
            cout << w << " ";
        }
        cout << endl;
    }();
    //引用捕获
    [&] {
        for (auto w : words) {
            cout << w << " ";
        }
        cout << endl;
    }();
    //混合捕获
    [=, &words] {
        for (auto w : words) {
            cout << w << " ";
        }
        cout << endl;
    }();

    //可变lambda
    [=]() mutable {
        words.insert(words.begin(), "mutable_lambda");
        for (auto w : words) {
            cout << w << " ";
        }
        cout << endl;
    }();

    //指定lambda返回值
    vector<int> vi = {1, -2, -3, 4, 5};
    transform(vi.begin(), vi.end(), vi.begin(), [](int i) -> int {
        if (i < 0) return -i;
        return i;
    });
    [=] {
        for (auto i : vi) {
            cout << i << " ";
        }
        cout << endl;
    }();

    return 0;
}