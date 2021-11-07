#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string a;

    while (getline(cin, a)) {
        try {
            int p = a.find("throw", 0);
            if (p != -1) {
                throw runtime_error(a.substr(5));
            }
        } catch (runtime_error err) {
            cout << "Error: " << err.what() << endl;
            cout << "continue (y or n) ?";
            char n = cin.get();
            if (!cin || n == 'n') {
                cout << "terminated" << endl;
                break;
            } else {
                cout << "canceled" << endl;
            }
        }
    }

    return 0;
}