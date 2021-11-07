#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string lastWord;
    string currWord;

    int times = 0;
    int maxTimes = 0;
    string maxWord;
    while (cin >> currWord) {
        if (currWord == lastWord) {
            times++;
            if (times > maxTimes) {
                maxWord = currWord;
                maxTimes = times;
            }
        } else {
            times = 0;
            lastWord = currWord;
        }
    }

    if (maxTimes != 0) {
        cout << "word " << maxWord << " occured " << maxTimes + 1 << " times" << endl;
    } else {
        cout << "no word repeated!" << endl;
    }
}