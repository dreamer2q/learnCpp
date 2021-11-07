/*
 * File Created: Tuesday, 23rd June 2020 11:41:59 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 23rd June 2020 11:54:48 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
#include <fstream>

using namespace std;

class student {
private:
    int index;
    string name;
    float score;

public:
    student(int ind = 0, string nm = "", float sc = 0) : index(ind), name(nm), score(sc) {}
    friend ostream& operator<<(ostream& out, const student& st) {
        out << st.index << " " << st.name << " " << st.score << endl;
        return out;
    };
    friend istream& operator>>(istream& in, student& st) {
        in >> st.index >> st.name >> st.score;
        return in;
    };
};

int main() {
    fstream fin("stu.txt", ios_base::out | ios_base::in);
    if (!fin) {
        cerr << "打开文件失败" << endl;
        return -1;
    }
    student st1, st2;
    cin >> st1 >> st2;
    fin << st1 << st2;

    fin.seekg(ios::seekdir::_S_beg);

    student fu1, fu2;
    fin >> fu1 >> fu2;
    cout << fu1 << fu2;

    fin.close();
    return 0;
}