/*
 * File Created: Tuesday, 16th June 2020 8:43:35 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 16th June 2020 9:33:53 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

/*
C++中的异常处理
*/

#include <bits/stdc++.h>

using namespace std;

//定义接口
class Exception {
public:
    Exception() {}
    ~Exception() {}
    virtual string what() const = 0;
};

class OutOfMemory : public Exception {
public:
    OutOfMemory(string s) : size(s) {}

    string what() const {
        return "allocate " + size + " memory fail";
    }

private:
    string size;
};

class RangeError : public Exception {
public:
    RangeError(int i, int r) : index(i), range(r) {}
    string what() const {
        return "index " + to_string(index) + " is out of range " + to_string(range);
    }

private:
    int index, range;
};

int main() {
    try {
        throw OutOfMemory("10G");
    } catch (Exception& e) {
        cerr << e.what() << endl;
    }
    try {
        throw RangeError(10, 5);
    } catch (Exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}