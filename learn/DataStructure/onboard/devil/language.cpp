#include <bits/stdc++.h>

//��ߣ��list����
#include "m_list.h"

using namespace std;

// ����ħ�����Ե�ת������
map<char, string> rule = {
    {'A', "sae"},
    {'B', "tAdA"},
};

//����ǰ������
void transParentheses(MyList<char>& out, stringstream& ss);

// ħ�����Է��뺯��
void trans(MyList<char>& out, string s) {
    stringstream ss(s);  //����һ��������
    char token;
    while (ss >> token) {             //ÿ��ȡ��һ��token���з���
        if (isupper(token)) {         //��С�û�����
            trans(out, rule[token]);  //�ݹ鴦��Ƕ�׵����
        } else if (token == '(') {    //����()�Ĺ���
            out.push_back(token);
            transParentheses(out, ss);  //�ݹ鴦��
        } else {
            //����Ҫ������ַ������������
            out.push_back(token);
        }
    }
}

void transParentheses(MyList<char>& out, stringstream& ss) {
    char divider, token;
    ss >> divider;
    while (ss >> token) {    //�Ӵ�������
        if (token == '(') {  // ( Ƕ�״���
            out.push_back(token);
            transParentheses(out, ss);  //�ݹ鴦������Ƕ��
        } else if (token == ')') {      //��ȡ�� )
            string lst;                 //չ����������
            lst.push_back(divider);
            while ((token = out.back()) != '(') {  //���� (
                out.pop_back();
                lst.push_back(token);
                lst.push_back(divider);
            }
            out.pop_back();   // ���� (
            trans(out, lst);  //������ܵĹ���
            break;
        } else {
            out.push_back(token);  //token�����
        }
    }
}

int main() {
    cout << "\tħ������\n"
         << endl;
    cout << "��ǰת������\n"
         << endl;

    //���뵱ǰ��ת������
    for (auto& r : rule) {
        cout << r.first << " -> " << r.second << endl;
    }
    cout << endl;

    cout << "������ħ��˵�Ļ�: ";
    string sentence;
    cin >> sentence;
    MyList<char> lst;
    trans(lst, sentence);  //����ħ������
    //���ת���Ľ��
    for (auto it = lst.begin(); it != lst.end(); it++) {
        cout << *it;
    }
    cout << endl;
    //����
    system("pause");
    return 0;
}
