#include <iostream>

using namespace std;

class Store {
   public:
    friend istream& operator>>(istream& is, Store& s) {
        int num, n;
        double price;
        double sum = 0;

        is >> num >> n >> price;

        sum = n * price;
        if (n >= 10) {
            sum *= s.discount;
        }
        s.totalSum += sum;
        s.count += n;
        return is;
    }
    friend ostream& operator<<(ostream& os, Store& s) {
        os.flags(ios::fixed);
        os.precision(2);
        os << s.totalSum << " " << s.totalSum / s.count;
        return os;
    }

   private:
    static double discount;
    static double totalSum;
    static int count;
};
double Store::discount = 0.98;
double Store::totalSum = 0;
int Store::count = 0;

int main() {
    Store store;
    int n;
    cin >> n;
    while (n--) {
        cin >> store;
    }
    cout << store << endl;

    return 0;
}
