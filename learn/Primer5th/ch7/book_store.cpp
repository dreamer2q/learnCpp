
#include <iostream>
#include <string>

#include "sales_data.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
    Sales_data total;
    if (read(cin, total)) {
        Sales_data trans;
        while (read(cin, trans)) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
        return 0;
    } else {
        cout << "No data" << endl;
        return -1;
    }
}