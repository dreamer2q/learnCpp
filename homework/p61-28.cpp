

#include <iostream>

using namespace std;

char menu() {
    cout << "Menu:" << endl
         << "A(dd)" << endl
         << "D(elete)" << endl
         << "S(ort)" << endl
         << "Q(uit)" << endl;
    cout << "Select one:";
    char r;
    cin >> r;
    return r;
}

int main() {
    char ch;
    while ((ch = menu()) != 'Q') {
        switch (ch) {
            case 'A':
                cout << "数据已增加" << endl;
                break;
            case 'D':
                cout << "数据已删除" << endl;
                break;
            case 'S':
                cout << "数据已排序" << endl;
                break;
        }
    }

    return 0;
}
