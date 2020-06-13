/*
 * File Created: Friday, 12th June 2020 8:03:20 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Saturday, 13th June 2020 10:58:06 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
#include <cstring>
using namespace std;

class CMyString {
public:
    CMyString() {}
    CMyString(const char* str)
        : _M_str(do_construct(str)) {}
    //拷贝构造
    CMyString(const CMyString& cstr)
        : _M_str(do_construct(cstr._M_str)) {}
    //移动构造
    CMyString(CMyString&& cstr)
        : _M_str(cstr._M_str) {
        cstr._M_str = nullptr;
    }
    ~CMyString() {
        delete[] _M_str;
    }

    friend CMyString operator+(const CMyString& lhs, const CMyString& rhs) {
        auto len = strlen(lhs._M_str) + strlen(rhs._M_str) + 1;
        char* cstr = new char[len];
        strcpy(cstr, lhs._M_str);
        strcat(cstr, rhs._M_str);
        CMyString mstr;
        mstr._M_str = cstr;
        return mstr;
    }

    //移动赋值
    CMyString& operator=(CMyString&& cstr) {
        _M_str = cstr._M_str;
        cstr._M_str = nullptr;
        return *this;
    }

    //拷贝赋值,需要处理自己赋值给自己的特殊情况。
    CMyString& operator=(const CMyString& cstr) {
        char* newStr = do_construct(cstr._M_str);
        delete[] _M_str;
        _M_str = newStr;
        return *this;  //需要返回一个自身的引用，与内置类似保持一致。
    }

    friend ostream& operator<<(ostream& is, const CMyString& str) {
        is << str._M_str;
        return is;
    }

private:
    char* _M_str = nullptr;
    char* do_construct(const char* str) {
        if (str == nullptr) return nullptr;
        auto len = strlen(str) + 1;
        char* ret = new char[len];
        strcpy(ret, str);
        return ret;
    }
};

int main() {
    CMyString s1("Good "), s2("morning"), s3("evening"), s;
    s1 = s1;  //需要处理自己给自己赋值的情况，这个很重要
    s = s1 + s2;
    cout << s << endl;
    s = s1 + s3;
    cout << s << endl;
}