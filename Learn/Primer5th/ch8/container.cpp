
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> vs;

    vs.emplace(vs.end(), "123123");
    vs.emplace_back(80, 'c');

    string l = "石头";
    vs.push_back("doit");
    vs.push_back(l);

    vs.pop_back();

    //resize operation
    //容器大小变小后多余的元素会被删除
    vs.resize(1);

    //超出原来的大小后
    vs.resize(10, "new added");
    vs.insert(vs.end(), "test");
    cout << "capacity: " << vs.capacity() << endl;

    cout << "vector<string>: ";
    for (const auto& s : vs) {
        cout << s << " ";
    }
    cout << endl;

    // cout << vs.size() << endl;
    // cout << vs.empty() << endl;

    // //out of range test
    // vector<int> vi;
    // cout << vi.at(0) << endl;
    // cout << vi.at(-1) << endl;

    //forwoard_list 操作
    //由于这是一个单向的链表，
    //单项链表的删除，增加操作莫一个元素需要知道前面一个元素的位置
    //因此，forwoard_list提供的操作和其它的标准容器有些不同
    //可以关注一个before_begin()

    forward_list<string> fls;

    fls.insert_after(fls.before_begin(), {"cao", "ni", "ma", "de"});

    cout << "forward_list<string>: ";
    for (const auto& e : fls) {
        cout << e << " ";
    }
    cout << endl;

    //string 提供的额外操作

    string str = "this is a string";

    //substr
    cout << str.substr(1, 10) << endl;
    cout << str.substr(10) << endl;

    //改变大小的操作
    cout << str.insert(str.size(), " inserted from insert()") << endl;
    const char* cp = "a const char standing a string";
    cout << str.assign(cp) << endl;
    cout << str.append(" appended") << endl;
    cout << str.replace(0, 1, "this is a") << endl;

    //搜索操作
    auto res = str.find("standing");
    if (res != string::npos) {
        cout << "search failed" << endl;
    }
    cout << res << endl;

    //数值转换
    string t = to_string(123123.321312);
    cout << t << endl;

    double d = stod(t);
    cout << d << endl;

    return 0;
}