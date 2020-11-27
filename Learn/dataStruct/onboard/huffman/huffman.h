#ifndef __HUFFMAN__H__
#define __HUFFMAN__H__

#include <bits/stdc++.h>
using namespace std;

#define MAX_VAL 10000

struct HTnode {
    char ch;
    int weight;
    int parent;
    int left, right;
};

struct HuffTree {
    HTnode* ht;
    int size;
};

void InitHuffTree(HuffTree& ht, int n) {
    ht.ht = new HTnode[2 * n - 1];
    ht.size = 2 * n - 1;
}

void DestroyHuffTree(HuffTree& ht) {
    delete[] ht.ht;
    ht.size = 0;
}

//在前i个节点中选择，parent为-1且weight最小的节点，返回其序号
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

//s1 为二者总最小的那个
void Select(HuffTree& ht, int i, int& s1, int& s2) {
    s1 = MinVal(ht, i);
    s2 = MinVal(ht, i);
    if (s1 > s2) swap(s1, s2);
}

//根据字符表和权值，建立哈夫曼数
void CreateHuffTree(HuffTree& ht, int n, char ch[], int w[]) {
    if (n > 1) {
        //初始化数据表
        for (int i = 0; i < n; i++) {
            ht.ht[i].ch = ch[i];
            ht.ht[i].weight = w[i];
            ht.ht[i].parent = -1;
            ht.ht[i].left = ht.ht[i].right = -1;
        }

        //选择其中两个无parent，且权值最小的两个节点，作为s1,s2
        for (int i = n; i < ht.size; i++) {
            int s1, s2;
            Select(ht, i, s1, s2);
            ht.ht[s1].parent = ht.ht[s2].parent = i;
            ht.ht[i].left = s1;
            ht.ht[i].right = s2;
            ht.ht[i].weight = ht.ht[s1].weight + ht.ht[s2].weight;  //两颗子树的权值之和
            ht.ht[i].parent = -1;                                   //没有parent
            ht.ht[i].ch = ' ';                                      //非树叶节点无字符(空格)
        }
    }
}

//打印哈夫曼树
void Display(HuffTree& ht) {
    cout << "哈夫曼树静态链表\n"
         << endl;
    cout << "下标\t"
         << "字符\t"
         << "权值\t"
         << "左节点\t"
         << "右节点"
         << "双亲" << endl;
    auto h = ht.ht;
    for (int i = 0; i < ht.size; i++) {
        cout << i << "\t" << h[i].ch << "\t" << h[i].weight << "\t" << h[i].left << "\t" << h[i].right << "\t" << h[i].parent << endl;
    }
    cout << endl;
}

struct HCnode {
    char ch;
    char* str;
};

struct HuffEncoder {
    HCnode* hc;
    int size;
};

void InitHuffEncoder(HuffEncoder& hc, int n) {
    hc.hc = new HCnode[n];
    hc.size = n;
}

void DestroyHuffEncoder(HuffEncoder& hc) {
    for (int i = 0; i < hc.size; i++) {
        delete[] hc.hc[i].str;
    }
    delete[] hc.hc;
    hc.size = 0;
}

void CreateBook(HuffEncoder& hc, HuffTree& ht) {
    char* cd = new char[hc.size]{0};
    cd[hc.size - 1] = '\0';
    for (int i = 0; i < hc.size; i++) {
        int s = hc.size - 1;
        hc.hc[i].ch = ht.ht[i].ch;
        for (int c = i, f = ht.ht[i].parent; f != -1; c = f, f = ht.ht[f].parent) {
            cd[--s] = ht.ht[f].left == c ? '0' : '1';
        }
        hc.hc[i].str = new char[hc.size - s]{0};
        memcpy(hc.hc[i].str, cd + s, hc.size - s - 1);
    }
    delete[] cd;
}

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
