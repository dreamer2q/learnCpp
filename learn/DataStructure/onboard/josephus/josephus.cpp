#include "cycle_link_list.h"

struct PersonItem {
    int loc;   //这个人所在位序
    int pass;  //这个人所持有的密码

    bool operator==(const PersonItem& p) {
        return loc == p.loc && pass == p.pass;
    }
};

using namespace std;

int main() {
    cout << "约瑟夫环\n"
         << endl;
    int personCount;
    cout << "人数: ";
    cin >> personCount;
    if (personCount <= 0) {
        cout << "人数错误" << endl;
        return -1;
    }
    CycleList<PersonItem> cycle;  //定义一个循环链表的变量
    //给链表添加元素
    for (int i = 1; i <= personCount; i++) {
        int password;
        cout << "第" << i << "个人的密码：";
        cin >> password;
        cycle.push_back({i, password});  //在链表的末尾插入元素
    }
    cout << endl;

    cout << "\n当前循环链表的中的元素依次为" << endl;
    cycle.visit([](PersonItem& item) {  //遍历链表，输出每一个元素的内容
        cout << "位置 " << item.loc << ", 密码 " << item.pass << endl;
    });
    cout << "\n"
         << endl;

    cout << "初始密码：";
    int pass, seq = 1;
    cin >> pass;  //获取初始密码
    //模拟循环体
    for (auto it = cycle.begin(); cycle.length(); cycle.remove(it)) {    //每次循环删除一个元素
        it += (pass - 1) % cycle.length();                               //取模，速度提升
        cout << "第" << seq++ << "出列的位序是：" << (*it).loc << endl;  //输出出列的人
        pass = (*it).pass;                                               //获取他的密码，作为下一次遍历的密码
    }
    getchar();
    getchar();
    //结束退出
    return 0;
}