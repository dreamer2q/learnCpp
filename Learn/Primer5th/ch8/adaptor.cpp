/*
by dreamer2q

2020年5月13日

容器配适器
stack
queue
priority_queue
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    stack<int> stk;

    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);
    stk.push(5);
    stk.push(10);

    while (!stk.empty()) {
        auto tmp = stk.top();
        cout << tmp << " ";
        stk.pop();
    }
    cout << endl;

    const char* p[] = {
        "string1",
        "string2",
        "strin3",
    };

    //使用其它容器
    //配适器屏蔽了对容器的操作，并且不同的配适器对容器具有的操作不同
    stack<string, vector<string>> stks;

    stks.push("this is a string");
    stks.push("this is an another string");

    return 0;
}
