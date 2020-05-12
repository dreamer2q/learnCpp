#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <iomanip>

using namespace std;

int main() {
    fstream fin("fstreamDemo.cpp");
    string line;
    int index = 1;
    while (getline(fin, line)) {
        cout << setw(6) << left << index++ << line << endl;
    }
    return 0;
}
