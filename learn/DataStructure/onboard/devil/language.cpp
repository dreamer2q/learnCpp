#include <bits/stdc++.h>

//手撸的list队列
#include "m_list.h"

using namespace std;

// 定义魔王语言的转换规则
map<char, string> rule = {
    {'A', "sae"},
    {'B', "tAdA"},
};

//函数前置声明
void transParentheses(MyList<char>& out, stringstream& ss);

// 魔王语言翻译函数
void trans(MyList<char>& out, string s) {
    stringstream ss(s);  //构造一个输入流
    char token;
    while (ss >> token) {             //每次取出一个token进行翻译
        if (isupper(token)) {         //大小置换规则
            trans(out, rule[token]);  //递归处理嵌套的情况
        } else if (token == '(') {    //处理()的规则
            out.push_back(token);
            transParentheses(out, ss);  //递归处理
        } else {
            //不需要翻译的字符，存入队列中
            out.push_back(token);
        }
    }
}

void transParentheses(MyList<char>& out, stringstream& ss) {
    char divider, token;
    ss >> divider;
    while (ss >> token) {    //子处理流程
        if (token == '(') {  // ( 嵌套处理
            out.push_back(token);
            transParentheses(out, ss);  //递归处理括号嵌套
        } else if (token == ')') {      //读取到 )
            string lst;                 //展开括号内容
            lst.push_back(divider);
            while ((token = out.back()) != '(') {  //处理到 (
                out.pop_back();
                lst.push_back(token);
                lst.push_back(divider);
            }
            out.pop_back();   // 处理 (
            trans(out, lst);  //处理可能的规则
            break;
        } else {
            out.push_back(token);  //token入队列
        }
    }
}

int main() {
    cout << "\t魔王语言\n"
         << endl;
    cout << "当前转换规则：\n"
         << endl;

    //输入当前的转换规则
    for (auto& r : rule) {
        cout << r.first << " -> " << r.second << endl;
    }
    cout << endl;

    cout << "请输入魔王说的话: ";
    string sentence;
    cin >> sentence;
    MyList<char> lst;
    trans(lst, sentence);  //翻译魔王语言
    //输出转换的结果
    for (auto it = lst.begin(); it != lst.end(); it++) {
        cout << *it;
    }
    cout << endl;
    //结束
    system("pause");
    return 0;
}
