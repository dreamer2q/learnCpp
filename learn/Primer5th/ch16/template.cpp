#include <bits/stdc++.h>

using namespace std;

template <typename T>
int compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

int main() {
    cout << compare(string("Hello"), string("world")) << endl;

    return 0;
}
