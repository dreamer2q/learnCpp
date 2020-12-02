#ifndef __HUFFMAN__H__
#define __HUFFMAN__H__

#include <bits/stdc++.h>
using namespace std;

// 最大节点数
#define MAX_VAL 10000

//树的节点
struct HTnode {
    char ch;          // 节点保存的字符
    int weight;       // 字符对应的权重
    int parent;       // 父节点对应的坐标, -1 表示无
    int left, right;  // 左孩子，右孩子，-1 表示无
};

struct HuffTree {
    HTnode* ht;  //指向一个节点的静态数组，需要自己管理内存
    int size;    //树的节点数量
};

// 初始化一个哈夫曼树
// @ht  需要初始化的结构体
// @n   需要编码的字符数
void InitHuffTree(HuffTree& ht, int n) {
    ht.ht = new HTnode[2 * n - 1];
    ht.size = 2 * n - 1;
}

// 释放一颗哈夫曼树
// @ht 需要释放的结构体
void DestroyHuffTree(HuffTree& ht) {
    delete[] ht.ht;
    ht.size = 0;
}

// 在前i个节点中选择，无父节点(-1)且权值(weight)最小的节点，返回其序号
// @ht      哈夫曼树
// @index   在前index个节点
int MinVal(HuffTree& ht, int index) {
    int min = MAX_VAL, k = 0;
    for (int i = 0; i < index; i++) {
        if (ht.ht[i].parent == -1 && ht.ht[i].weight < min) {
            min = ht.ht[i].weight;
            k = i;
        }
    }
    ht.ht[k].parent = MAX_VAL;
    return k;
}

// 在前i个节点中，选出两个无父节点且权重最小的两个节点
///******************
// @ht  哈夫曼树
// @i   前i个节点
// @s1  返回s1的序号
// @s2  返回s2的序号
///******************
// s1 为二者中较小者
void Select(HuffTree& ht, int i, int& s1, int& s2) {
    s1 = MinVal(ht, i);
    s2 = MinVal(ht, i);
    if (s1 > s2) swap(s1, s2);
}

// 根据字符表和权值，建立哈夫曼树
// @ht  哈夫曼树
// @n   需要编码的字符数量
// @ch  需要编码的字符
// @w   字符对应的权重
void CreateHuffTree(HuffTree& ht, int n, char ch[], int w[]) {
    if (n > 1) {
        //初始化二叉树集合
        for (int i = 0; i < n; i++) {
            ht.ht[i].ch = ch[i];
            ht.ht[i].weight = w[i];
            ht.ht[i].parent = -1;
            ht.ht[i].left = ht.ht[i].right = -1;
        }

        //从节点集合中选出两个无父节点且权值最小的两颗树
        //组成一个新的树放入集合中
        //其中新树的权值是两个节点权值之和
        for (int i = n; i < ht.size; i++) {
            int s1, s2;
            Select(ht, i, s1, s2);                                  //选择s1, s2
            ht.ht[s1].parent = ht.ht[s2].parent = i;                //构造新二叉树
            ht.ht[i].left = s1;                                     //s1作为左子节点，编码为0
            ht.ht[i].right = s2;                                    //s2作为右节点，编码为1
            ht.ht[i].weight = ht.ht[s1].weight + ht.ht[s2].weight;  //两颗子树的权值之和
            ht.ht[i].parent = -1;                                   //没有parent
            ht.ht[i].ch = ' ';                                      //非树叶节点无字符(空格)
        }
    }
}

//打印哈夫曼树的静态链表
// @ht 哈夫曼树
void Display(HuffTree& ht) {
    cout << "哈夫曼树静态链表\n"
         << "下标\t"
         << "字符\t"
         << "权值\t"
         << "左节点\t"
         << "右节点\t"
         << "双亲" << endl;
    auto h = ht.ht;
    for (int i = 0; i < ht.size; i++) {
        cout << i << "\t" << h[i].ch << "\t" << h[i].weight << "\t" << h[i].left << "\t" << h[i].right << "\t" << h[i].parent << endl;
    }
    cout << endl;
}

//解码结果
struct HCnode {
    char ch;
    char* str;
};

//哈夫曼树编码器
struct HuffEncoder {
    HCnode* hc;  //解码结果
    int size;    //数组大小
};

//初始化编码器
// @ht 编码器
// @n  字符数
void InitHuffEncoder(HuffEncoder& hc, int n) {
    hc.hc = new HCnode[n];
    hc.size = n;
}

//释放编码器
// @hc 编码器
void DestroyHuffEncoder(HuffEncoder& hc) {
    for (int i = 0; i < hc.size; i++) {
        delete[] hc.hc[i].str;
    }
    delete[] hc.hc;
    hc.size = 0;
}

//根据哈夫曼树创建编码对照表
// @hc 哈夫曼树
// @ht 编码器
void CreateBook(HuffEncoder& hc, HuffTree& ht) {
    for (int i = 0; i < hc.size; i++) {
        hc.hc[i].ch = ht.ht[i].ch;
        string ce;
        for (int c = i, p = ht.ht[i].parent; p != -1; c = p, p = ht.ht[p].parent) {
            ce.insert(ce.begin(), "10"[ht.ht[p].left == c]);
        }
        hc.hc[i].str = new char[ce.size() + 1]{0};
        memcpy(hc.hc[i].str, ce.c_str(), ce.size());
    }
}

//对字符串进行编码并输出到终端和文件
//字符需要是编码字符集的子集
// @hc  编码器
// @ch  需要编码的字符集
void Encode(HuffEncoder& hc, char ch[]) {
    ofstream out("f1.txt", ios::out);
    for (int i = 0; i < strlen(ch); i++) {
        for (int j = 0; j < hc.size; j++) {
            if (ch[i] == hc.hc[i].ch) {
                out << hc.hc[i].str;
                cout << hc.hc[i].str;
                break;
            }
        }
    }
    out.close();
    cout << endl;
}

//解码文件中的经过编码的二进制
// @ht 哈夫曼树
void Decode(HuffTree& ht) {
    char ch[256] = {0};
    ifstream in("f2.txt", ios::in);
    in >> ch;
    in.close();
    cout << "需要译码的二进制电文是: " << ch << endl;
    cout << "译码结果: ";
    for (int i = 0; i < strlen(ch); i--) {
        int p = ht.size - 1, pre = -1;
        while (p != -1) {
            pre = p;
            p = ch[i] == '0' ? ht.ht[p].left : ht.ht[p].right;
            i++;
        }
        cout << ht.ht[pre].ch;
    }
    cout << endl;
}

#endif
