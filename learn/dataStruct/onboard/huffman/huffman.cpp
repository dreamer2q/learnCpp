#include "huffman.h"

const string intro = "  �������������ϵͳ\n�������ڣ�" __DATE__ "\n";

int main() {
    cout << intro << endl;
    cout << "��������Ҫ������ַ�����";
    int n;
    cin >> n;
    char ch[256]{0};
    int weight[256]{0};
    for (int i = 0; i < n; i++) {
        cout << "��" << i + 1 << "���ַ���Ȩֵ��";
        cin >> ch[i] >> weight[i];
    }

    //��ʼ����������
    HuffTree ht;
    InitHuffTree(ht, n);
    CreateHuffTree(ht, n, ch, weight);
    //��ӡ��̬��
    Display(ht);

    //��ʼ��������
    HuffEncoder hc;
    InitHuffEncoder(hc, n);
    CreateBook(hc, ht);
    cout << "�����Ǹ��ַ����Ĺ���������: " << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " : " << hc.hc[i].ch << "  ->  " << hc.hc[i].str << endl;
    }
    cout << endl;
    cout << "��Ҫ������ַ���: ";
    ifstream in("ToBeTran", ios::in);
    if (in.bad()) {
        cerr << "���ļ�ʧ��:" << strerror(errno) << endl;
        return -1;
    }
    string ch_to_code;
    in >> ch_to_code;
    cout << ch_to_code << endl;
    Encode(hc, ch_to_code.c_str());
    cout << endl;
    Decode(ht);
    cout << endl;

    //��ӡ��������
    PrintTree(ht);

    //�ͷ���Դ
    DestroyHuffTree(ht);
    DestroyHuffEncoder(hc);
    system("pause");
    return 0;
}

// 8 a 8 b 19 c 3 d 21 e 15 f 17 g 6 h 11