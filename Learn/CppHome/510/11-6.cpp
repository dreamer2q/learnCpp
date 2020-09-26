/*
 * File Created: Tuesday, 16th June 2020 7:13:25 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 16th June 2020 8:29:07 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

class Dog {
public:
    Dog() : Dog(0, 0) {}
    Dog(unsigned a, unsigned w) : age(a), weight(w) {}

    void display() {
        cout << "Age: " << age << endl;
        cout << "Weight: " << weight << endl;
    }

    friend ostream& operator<<(ostream& os, const Dog& d) {
        os << d.age << " " << d.weight << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Dog& d) {
        is >> d.age >> d.weight;
        return is;
    }

private:
    int age;
    int weight;
};

//文本文件
void ascii() {
    fstream file;
    file.open("dog.txt", ios_base::out);
    if (file.fail()) {
        cerr << "open file failed" << endl;
        exit(-1);
    }
    Dog dog1(10, 5);
    dog1.display();
    //写入到文件
    file << dog1;
    file.close();

    file.open("dog.txt", ios_base::in);
    Dog dog2;
    //从文件中读取
    file >> dog2;
    dog2.display();
    file.close();
}

//二进制文件
void binary() {
    fstream file;
    file.open("dog.bin", ios_base::binary | ios_base::out);
    if (file.fail()) {
        cerr << "open file failed" << endl;
        exit(-1);
    }
    Dog dog1(10, 5);
    dog1.display();
    file << dog1;
    file.close();
    file.open("dog.bin", ios_base::binary | ios_base::in);
    Dog dog2;
    file >> dog2;
    dog2.display();
    file.close();
}

int main() {
    ascii();
    binary();
    return 0;
}