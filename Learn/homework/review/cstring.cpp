/*
 * File Created: Friday, 12th June 2020 8:03:20 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Friday, 12th June 2020 9:42:54 pm
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
    CMyString() {
        _M_str = nullptr;
    }
    CMyString(const char* str) : CMyString() {
        do_construct(str);
    }
    CMyString(const CMyString& cstr) : CMyString() {
        do_construct(cstr._M_str);
    }
    CMyString(CMyString&& cstr) : CMyString() {
        _M_str = cstr._M_str;
        cstr._M_str = nullptr;
    }
    ~CMyString() {
        do_destruct();
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
    void operator=(CMyString&& cstr) {
        do_destruct();
        _M_str = cstr._M_str;
        cstr._M_str = nullptr;
    }
    void operator=(const CMyString& cstr) {
        do_destruct();
        do_construct(cstr._M_str);
    }

    friend ostream& operator<<(ostream& is, const CMyString& str) {
        is << str._M_str;
        return is;
    }

private:
    char* _M_str;
    void do_construct(const char* str) {
        if (str != nullptr) {
            auto len = strlen(str) + 1;
            _M_str = new char[len];
            strcpy(_M_str, str);
        }
    }
    void do_destruct() {
        if (_M_str != nullptr) {
            delete[] _M_str;
            _M_str = nullptr;
        }
    }
};

int main() {
    CMyString s1("Good "), s2("morning"), s3("evening"), s;
    s = s1 + s2;
    cout << s << endl;
    s = s1 + s3;
    cout << s << endl;
}