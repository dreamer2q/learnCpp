#include <bits/stdc++.h>

using namespace std;

class DisjointSet {
   public:
    void Reset(int n) {
        m_set = vector<int>(n + 1, 0);
    }
    int find(int x) {
        if (m_set[x] == 0) return x;
        return (m_set[x] = find(m_set[x]));
    }
    bool Merge(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb) return false;
        m_set[pa] = pb;
        return true;
    }
    int DisjointNumber() {
        int counter = 0;
        for (const auto &i : m_set) {
            if (i == 0) counter++;
        }
        return counter - 1;  //去掉一个0位置的计数
    }

   private:
    vector<int> m_set;
};

int main() {
    DisjointSet ds;
    int n, m;
    while (cin >> n >> m) {
        ds.Reset(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            ds.Merge(a, b);
        }
        cout << ds.DisjointNumber() - 1 << endl;
    }
    return 0;
}