/**
 * 
 *  我吐了，我在干什么？？？？？？
 * 
 * 
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum Item {
    Road,
    Wall,
    Angel,
    Guard,
    Friend,
};

istream& operator>>(istream& in, Item& out) {
    char c;
    cin >> c;
    if (c == '.')
        out = Road;
    else if (c == '#')
        out = Wall;
    else if (c == 'a')
        out = Angel;
    else if (c == 'x')
        out = Guard;
    else if (c == 'r')
        out = Friend;
    return in;
}
struct person {
    int pos;
    int dist;
};
bool operator<(const person& a, const person& b) {
    return a.dist > b.dist;
}
class Jail {
   public:
    Jail(int n, int m) : m_height(n), m_witdh(m) {
        dir[0] = -m;
        dir[1] = m;
        dir[2] = 1;
        dir[3] = -1;
    }
    friend istream& operator>>(istream& in, Jail& a) {
        for (int i = 0; i < a.m_height * a.m_witdh; i++) {
            Item im;
            in >> im;
            a.m_map.push_back(im);
            if (im == Angel) a.ang = person{i, 0};
        }
        return in;
    }
    int bfs() {
        int v[40001] = {0};
        q.push(ang);
        v[ang.pos] = 1;
        while (!q.empty()) {
            auto cur = q.top();
            q.pop();
            if (m_map[cur.pos] == Friend) {
                return cur.dist;
            }

            //find sub movable nodes
            for (auto d : dir) {
                auto nex = person{
                    cur.pos + d,
                    cur.dist + 1,
                };
                if (d == 1 || d == -1)
                    if (nex.pos % m_witdh == 0) continue;
                if (nex.pos < 0 || nex.pos >= m_witdh * m_height) continue;
                if (v[nex.pos]) continue;
                switch (m_map[nex.pos]) {
                    case Friend:
                        return nex.dist;
                    case Guard:
                        nex.dist++;
                    case Road:
                        q.push(nex);
                        v[nex.pos] = 1;
                }
            }
        }
        return -1;
    }

   private:
    int m_witdh, m_height;
    vector<Item> m_map;
    person ang;
    priority_queue<person> q;
    int dir[4];
};

int main() {
    int n, m;
    while (cin >> n >> m) {
        Jail j(n, m);
        cin >> j;
        int o = j.bfs();
        if (o == -1) {
            cout << "Poor ANGEL has to stay in the prison all his life." << endl;
        } else {
            cout << o << endl;
        }
    }
    return 0;
}