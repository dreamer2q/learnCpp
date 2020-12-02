#ifndef __HUFFMAN__H__
#define __HUFFMAN__H__

#include <bits/stdc++.h>
using namespace std;

// ���ڵ���
#define MAX_VAL 10000

//���Ľڵ�
struct HTnode {
    char ch;          // �ڵ㱣����ַ�
    int weight;       // �ַ���Ӧ��Ȩ��
    int parent;       // ���ڵ��Ӧ������, -1 ��ʾ��
    int left, right;  // ���ӣ��Һ��ӣ�-1 ��ʾ��
};

struct HuffTree {
    HTnode* ht;  //ָ��һ���ڵ�ľ�̬���飬��Ҫ�Լ������ڴ�
    int size;    //���Ľڵ�����
};

// ��ʼ��һ����������
// @ht  ��Ҫ��ʼ���Ľṹ��
// @n   ��Ҫ������ַ���
void InitHuffTree(HuffTree& ht, int n) {
    ht.ht = new HTnode[2 * n - 1];
    ht.size = 2 * n - 1;
}

// �ͷ�һ�Ź�������
// @ht ��Ҫ�ͷŵĽṹ��
void DestroyHuffTree(HuffTree& ht) {
    delete[] ht.ht;
    ht.size = 0;
}

// ��ǰi���ڵ���ѡ���޸��ڵ�(-1)��Ȩֵ(weight)��С�Ľڵ㣬���������
// @ht      ��������
// @index   ��ǰindex���ڵ�
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

// ��ǰi���ڵ��У�ѡ�������޸��ڵ���Ȩ����С�������ڵ�
///******************
// @ht  ��������
// @i   ǰi���ڵ�
// @s1  ����s1�����
// @s2  ����s2�����
///******************
// s1 Ϊ�����н�С��
void Select(HuffTree& ht, int i, int& s1, int& s2) {
    s1 = MinVal(ht, i);
    s2 = MinVal(ht, i);
    if (s1 > s2) swap(s1, s2);
}

// �����ַ����Ȩֵ��������������
// @ht  ��������
// @n   ��Ҫ������ַ�����
// @ch  ��Ҫ������ַ�
// @w   �ַ���Ӧ��Ȩ��
void CreateHuffTree(HuffTree& ht, int n, char ch[], int w[]) {
    if (n > 1) {
        //��ʼ������������
        for (int i = 0; i < n; i++) {
            ht.ht[i].ch = ch[i];
            ht.ht[i].weight = w[i];
            ht.ht[i].parent = -1;
            ht.ht[i].left = ht.ht[i].right = -1;
        }

        //�ӽڵ㼯����ѡ�������޸��ڵ���Ȩֵ��С��������
        //���һ���µ������뼯����
        //����������Ȩֵ�������ڵ�Ȩֵ֮��
        for (int i = n; i < ht.size; i++) {
            int s1, s2;
            Select(ht, i, s1, s2);                                  //ѡ��s1, s2
            ht.ht[s1].parent = ht.ht[s2].parent = i;                //�����¶�����
            ht.ht[i].left = s1;                                     //s1��Ϊ���ӽڵ㣬����Ϊ0
            ht.ht[i].right = s2;                                    //s2��Ϊ�ҽڵ㣬����Ϊ1
            ht.ht[i].weight = ht.ht[s1].weight + ht.ht[s2].weight;  //����������Ȩֵ֮��
            ht.ht[i].parent = -1;                                   //û��parent
            ht.ht[i].ch = ' ';                                      //����Ҷ�ڵ����ַ�(�ո�)
        }
    }
}

//��ӡ���������ľ�̬����
// @ht ��������
void Display(HuffTree& ht) {
    cout << "����������̬����\n"
         << "�±�\t"
         << "�ַ�\t"
         << "Ȩֵ\t"
         << "��ڵ�\t"
         << "�ҽڵ�\t"
         << "˫��" << endl;
    auto h = ht.ht;
    for (int i = 0; i < ht.size; i++) {
        cout << i << "\t" << h[i].ch << "\t" << h[i].weight << "\t" << h[i].left << "\t" << h[i].right << "\t" << h[i].parent << endl;
    }
    cout << endl;
}

//������
struct HCnode {
    char ch;
    char* str;
};

//��������������
struct HuffEncoder {
    HCnode* hc;  //������
    int size;    //�����С
};

//��ʼ��������
// @ht ������
// @n  �ַ���
void InitHuffEncoder(HuffEncoder& hc, int n) {
    hc.hc = new HCnode[n];
    hc.size = n;
}

//�ͷű�����
// @hc ������
void DestroyHuffEncoder(HuffEncoder& hc) {
    for (int i = 0; i < hc.size; i++) {
        delete[] hc.hc[i].str;
    }
    delete[] hc.hc;
    hc.size = 0;
}

//���ݹ�����������������ձ�
// @hc ��������
// @ht ������
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

//���ַ������б��벢������ն˺��ļ�
//�ַ���Ҫ�Ǳ����ַ������Ӽ�
// @hc  ������
// @ch  ��Ҫ������ַ���
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

//�����ļ��еľ�������Ķ�����
// @ht ��������
void Decode(HuffTree& ht) {
    char ch[256] = {0};
    ifstream in("f2.txt", ios::in);
    in >> ch;
    in.close();
    cout << "��Ҫ����Ķ����Ƶ�����: " << ch << endl;
    cout << "������: ";
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
