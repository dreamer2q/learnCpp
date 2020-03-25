
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> typeNames = {
        "bool",
        "char",
        "wchar_t",
        "short",
        "int",
        "long",
        "long long",
        "pointer*",
        "float",
        "double",
        "string",
        "vector<int>",
    };
    vector<int> typeSizes = {
        sizeof(bool),
        sizeof(char),
        sizeof(wchar_t),
        sizeof(short),
        sizeof(int),
        sizeof(long),
        sizeof(long long),
        sizeof(nullptr),
        sizeof(float),
        sizeof(double),
        sizeof(string),
        sizeof(vector<int>),
    };

    for (int i = 0; i < typeNames.size(); i++) {
        cout << typeNames[i] << " = " << typeSizes[i] << endl;
    }

    return 0;
}