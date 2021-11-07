#include <iostream>
#include <queue>

const int NMAX = 101;

using namespace std;

struct node {
    int S, N, M;
    int steps;
};

int gS, gN, gM;

bool doMove(const int A, int& a, const int B, int& b) {
    if (a != 0 && B != b) {
        if (B - b >= a) {
            b += a;
            a = 0;
        } else {
            a -= B - b;
            b = B;
        }
        return true;
    }
    return false;
}

#define v(n) visited[n.M][n.N]

void bfs() {
    bool visited[NMAX][NMAX] = {false};

    queue<node> q;
    node start{
        S : gS,
        N : 0,
        M : 0,
        steps : 0,
    };
    //visited[start.M][start.N] = true;
    v(start) = true;
    q.push(start);

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur.S == 0 && cur.M == cur.N ||
            cur.M == 0 && cur.S == cur.N ||
            cur.N == 0 && cur.S == cur.M) {
            cout << cur.steps << endl;
            return;
        }
        //检查所有子节点
        cur.steps++;
        node nex = cur;
        if (doMove(gS, nex.S, gM, nex.M) && !v(nex)) {
            v(nex) = true;
            q.push(nex);
        }
        nex = cur;
        if (doMove(gS, nex.S, gN, nex.N) && !v(nex)) {
            v(nex) = true;
            q.push(nex);
        }
        nex = cur;
        if (doMove(gM, nex.M, gS, nex.S) && !v(nex)) {
            v(nex) = true;
            q.push(nex);
        }
        nex = cur;
        if (doMove(gM, nex.M, gN, nex.N) && !v(nex)) {
            v(nex) = true;
            q.push(nex);
        }
        nex = cur;
        if (doMove(gN, nex.N, gS, nex.S) && !v(nex)) {
            v(nex) = true;
            q.push(nex);
        }
        nex = cur;
        if (doMove(gN, nex.N, gM, nex.M) && !v(nex)) {
            v(nex) = true;
            q.push(nex);
        }
    }
    cout << "NO" << endl;
}

int main() {
    while (cin >> gS >> gN >> gM) {
        if (gS == 0 && gN == 0 && gM == 0) break;
        bfs();
    }

    return 0;
}