#include <bits/stdc++.h>
using namespace std;
int randnum(int from, int to) {
    auto r = rand();
    return r % (to - from) + to;
}
int main() {
    srand(time(NULL));
    while (1) {
        vector<int> randArr;
        for (int i = 0; i < 10; i++) {
            randArr.push_back(randnum(1, 100));
        }
        ostream_iterator<int> out(cout, " ");
        copy(randArr.begin(), randArr.end(), out);
        cout << endl;
    }
    return 0;
}
