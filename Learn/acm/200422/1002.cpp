#include <iostream>
#include <vector>
using namespace std;

bool vis[20];
int n;
vector<int> v{1};
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
bool isPrime(int n) {
    for (const auto& p : primes) {
        if (p == n)
            return true;
    }
    return false;
}

void dfs() {
    if (v.size() == n) {
        for (int i = 0; i < n; i++) {
            cout << v[i];
            if (i != n - 1)
                cout << " ";
        }
        cout << endl;
    }
    for (int i = 2; i <= n; i++) {
        if (vis[i] == false && isPrime(i + v.back())) {
            if (v.size() == n - 1 && !isPrime(i + 1)) {
                continue;
            }
            vis[i] = true;
            v.push_back(i);
            dfs();
            v.pop_back();
            vis[i] = false;
        }
    }
}

int main() {
    int cas = 1;
    while (cin >> n) {
        cout << "Case " << cas++ << ":" << endl;
        dfs();
        cout << endl;
    }
    return 0;
}