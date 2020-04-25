#include <cmath>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int pow(char c, int i) {
    int tmp = 1;
    while (i--)
        tmp *= c;
    return tmp;
};

bool operator==(int target, const string& s) {
    int t = 0;
    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            t += pow(s[i] - 'A' + 1, i + 1);
        } else {
            t -= pow(s[i] - 'A' + 1, i + 1);
        }
    }
    return t == target;
}
int target;
string search;
priority_queue<string> q;
bool vis[20];
void dfs(string& s) {
    if (s.length() == 5 && target == s) {
        q.push(s);
    }
    if (s.length() >= 5)
        return;
    for (int i = 0; i < search.length(); i++) {
        if (vis[i] == false) {
            vis[i] = true;
            s.push_back(search[i]);
            dfs(s);
            s.pop_back();
            vis[i] = false;
        }
    }
}

int main() {
    while (cin >> target >> search) {
        if (target == 0 && search == "END")
            break;
        string s;
        dfs(s);
        if (q.empty()) {
            cout << "no solution" << endl;
            continue;
        }
        cout << q.top() << endl;
        while (!q.empty())
            q.pop();
    }

    return 0;
}