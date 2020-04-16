
#include <iostream>

using namespace std;

int set[10001];

int find(int x) {
    int r = x;
    while (set[r] != r)  //没到根节点
        r = set[r];
    return r;  //找到后返回
}

void merge(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if (ra != rb)
        set[ra] = rb;
}

int main() {
    int cases;
    cin >> cases;
    while (cases--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            set[i] = i;  //初始化集合
        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            merge(a, b);
        }
        int counter = 0;
        for (int i = 1; i <= n; i++)
            if (set[i] == i) counter++;
        cout << counter << endl;
    }
    return 0;
}