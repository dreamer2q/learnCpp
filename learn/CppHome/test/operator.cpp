/*
 * File Created: Tuesday, 23rd June 2020 10:56:32 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 23rd June 2020 12:01:48 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

class CArray {
public:
    int len;
    float *arp;

public:
    CArray(int n = 0);
    ~CArray() {
        if (arp) delete[] arp;
    }
    int GetLen() const { return len; }
    void SetLen(int l) {
        if (l > 0) {
            if (arp) delete[] arp;
            arp = new float[l];
            memset(arp, 0, sizeof(float) * l);  //A ���ÿ⺯������������Ĵ洢�ռ����Ϊ0��
            len = l;
        }
    }
    float &operator[](unsigned index) {
        if (index < len) {
            return arp[index];
        }
        stringstream str;
        str << "Eror ���±�" << index << "���磡";
        throw out_of_range(str.str());
    }
};

CArray::CArray(int n) {
    if (n > 0) {
        arp = new float[n];
        memset(arp, 0, sizeof(float) * n);
        len = n;
    } else {
        len = 0;
        arp = 0;
    }
}

int main() {
    CArray m1(10), m2(3);
    int i;
    for (i = 0; i < 10; i++)
        m1[i] = (float)i;       //���������±��ʹ��
    for (i = 1; i < 11; i++) {  //B m1 �е�*arp ���Ϊ10 ���ַ�
        try {
            cout << m1[i];
            if (i != 9) {
                cout << " ";
            }
        } catch (out_of_range e) {
            cout << endl
                 << e.what() << endl;
        }
    }
}