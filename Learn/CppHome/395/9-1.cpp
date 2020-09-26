/*
 * Copyright: MIT
 * ----
 * File: 9-1.cpp
 * File Created: Thursday, 28th May 2020 9:25:07 am
 * Author: dreamer2q (dreamer22qq@gmail.com)
 * Last Modified: Friday, 29th May 2020 11:21:20 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * 作业 9-1
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
class Array {
public:
    typedef T value_type;
    typedef size_t size_type;

    Array(size_t size) : m_size(size) {
        m_p = new T[size];
    }
    Array(const Array<T>& arr) : Array(arr.m_size) {
        memcpy(m_p, arr.m_p, sizeof(T) * m_size);
    }
    ~Array() {
        delete[] m_p;
    }

    Array<T>& operator=(const Array<T>& rhs) {
        this->m_size = rhs.m_size;
        delete[] m_p;
        m_p = new T[m_size];
        memcpy(m_p, rhs.m_p, sizeof(T) * m_size);
        return *this;
    }

    size_type size() const { return m_size; }

    // T& operator[](size_type i) {
    //     return m_p[i];
    // }

    operator T*() {
        return m_p;
    }
    operator const T*() const {
        return m_p;
    }

    T* begin() {
        return m_p;
    }
    T* end() {
        return m_p + m_size;
    }

private:
    T* m_p;
    size_t m_size;
};

int main() {
    int num;
    cout << "Input the number of students: ";
    cin >> num;

    Array<double> stu(num);
    for (int i = 0; i < stu.size(); i++) {
        cin >> stu[i];
    }

    double sum = accumulate(stu.begin(), stu.end(), 0.0);
    cout << "Average score is " << sum / stu.size() << endl;

    return 0;
}
