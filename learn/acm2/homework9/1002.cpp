#include <bits/stdc++.h>

using namespace std;

int target;
string sentence;
string pass;
map<char, bool> visit;
bool solved = false;

inline int N(int i, int p = 1) {
    auto r = pass[i] - 'A' + 1;
    int s = 1;
    while (p--) {
        s *= r;
    }
    return s;
}

bool f() {
    auto r = N(0) - N(1, 2) + N(3, 3) - N(4, 4) + N(5, 5);
    return r == target;
}

void dfs(int steps) {
    if (steps >= sentence.length()) return;
    auto c = sentence[steps];
    if (visit[c]) return;
    if (solved) return;
    visit[c] = true;
    pass.push_back(c);
    if (pass.length() == 5) {
        solved = f();
    } else {
        for (int i = steps + 1; i < sentence.length(); i++) {
            dfs(i);
        }
    }
    if (solved) return;
    pass.erase(pass.length() - 1);
    visit[c] = false;
}

int main() {
    while (cin >> target >> sentence) {
        pass.clear();
        visit.clear();
        dfs(0);
        if (solved) {
            cout << pass << endl;
        } else {
            cout << "no solution" << endl;
        }
    }
    return 0;
}
