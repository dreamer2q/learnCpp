#include "huffman.h"

const string intro = "  哈夫曼编码解码系统\n编译日期：" __DATE__ "\n";

int main() {
    cout << intro << endl;
    cout << "请输入需要编码的字符数：";
    int n;
    cin >> n;
    char ch[256]{0};
    int weight[256]{0};
    for (int i = 0; i < n; i++) {
        cout << "第" << i + 1 << "个字符和权值：";
        cin >> ch[i] >> weight[i];
    }

    //初始化哈夫曼树
    HuffTree ht;
    InitHuffTree(ht, n);
    CreateHuffTree(ht, n, ch, weight);
    //打印静态表
    Display(ht);

    //初始化编码器
    HuffEncoder hc;
    InitHuffEncoder(hc, n);
    CreateBook(hc, ht);
    cout << "下面是各字符串的哈夫曼编码: " << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " : " << hc.hc[i].ch << "  ->  " << hc.hc[i].str << endl;
    }
    cout << endl;
    cout << "需要编码的字符串: ";
    ifstream in("ToBeTran", ios::in);
    if (in.bad()) {
        cerr << "打开文件失败:" << strerror(errno) << endl;
        return -1;
    }
    string ch_to_code;
    in >> ch_to_code;
    cout << ch_to_code << endl;
    Encode(hc, ch_to_code.c_str());
    cout << endl;
    Decode(ht);
    cout << endl;

    //打印哈夫曼树
    PrintTree(ht);

    //释放资源
    DestroyHuffTree(ht);
    DestroyHuffEncoder(hc);
    system("pause");
    return 0;
}

// 8 a 8 b 19 c 3 d 21 e 15 f 17 g 6 h 11