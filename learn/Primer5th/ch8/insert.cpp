#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

int main() {
    auto t1 = GetTickCount();

    vector<int> v1;
    for (int i = 0; i < 90000000; i++) {
        // v1.insert(v1.begin(), i);
        v1.push_back(i);
    }

    cout << GetTickCount() - t1 << endl;

    return 0;
}