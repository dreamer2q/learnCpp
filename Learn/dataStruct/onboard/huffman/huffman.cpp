#include "huffman.h"

int main() {
    int n;
    cout << "huffman" << endl;
    cin >> n;
    char ch[256] = {0};
    int weight[256];

    for (int i = 0; i < n; i++) {
        cin >> ch[i] >> weight[i];
    }

    HuffTree ht;
    InitHuffTree(ht, n);
    CreateHuffTree(ht, n, ch, weight);
    Display(ht);

    HuffEncoder hc;
    InitHuffEncoder(hc, n);
    CreateBook(hc, ht);
    cout << "ÏÂÃæÊÇ¸÷×Ö·û´®µÄ¹þ·òÂü±àÂë: " << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " : " << hc.hc[i].ch << "  ->  " << hc.hc[i].str << endl;
    }
    cout << endl;
    cout << "string to encode: ";
    cin >> ch;
    Encode(hc, ch);
    Decode(ht);
    cout << endl;

    DestroyHuffTree(ht);
    DestroyHuffEncoder(hc);
    system("pause");
    return 0;
}

// 8 a 8 b 19 c 3 d 21 e 15 f 17 g 6 h 11