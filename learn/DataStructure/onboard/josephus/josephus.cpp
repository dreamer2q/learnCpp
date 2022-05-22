#include "cycle_link_list.h"

struct PersonItem {
    int loc;   //���������λ��
    int pass;  //����������е�����

    bool operator==(const PersonItem& p) {
        return loc == p.loc && pass == p.pass;
    }
};

using namespace std;

int main() {
    cout << "Լɪ��\n"
         << endl;
    int personCount;
    cout << "����: ";
    cin >> personCount;
    if (personCount <= 0) {
        cout << "��������" << endl;
        return -1;
    }
    CycleList<PersonItem> cycle;  //����һ��ѭ������ı���
    //���������Ԫ��
    for (int i = 1; i <= personCount; i++) {
        int password;
        cout << "��" << i << "���˵����룺";
        cin >> password;
        cycle.push_back({i, password});  //�������ĩβ����Ԫ��
    }
    cout << endl;

    cout << "\n��ǰѭ��������е�Ԫ������Ϊ" << endl;
    cycle.visit([](PersonItem& item) {  //�����������ÿһ��Ԫ�ص�����
        cout << "λ�� " << item.loc << ", ���� " << item.pass << endl;
    });
    cout << "\n"
         << endl;

    cout << "��ʼ���룺";
    int pass, seq = 1;
    cin >> pass;  //��ȡ��ʼ����
    //ģ��ѭ����
    for (auto it = cycle.begin(); cycle.length(); cycle.remove(it)) {    //ÿ��ѭ��ɾ��һ��Ԫ��
        it += (pass - 1) % cycle.length();                               //ȡģ���ٶ�����
        cout << "��" << seq++ << "���е�λ���ǣ�" << (*it).loc << endl;  //������е���
        pass = (*it).pass;                                               //��ȡ�������룬��Ϊ��һ�α���������
    }
    getchar();
    getchar();
    //�����˳�
    return 0;
}