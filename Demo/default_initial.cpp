#include <iostream>

using namespace std;

class Default {
   public:
    Default(int t) : r(t) {}
    static Default FromDefault() {}

    friend ostream& operator<<(ostream& os, const Default& d) {
        os << "c " << d.c << endl
           << "a " << d.a << endl
           << "b " << d.b << endl
           << "d " << d.d << endl
           << "l " << d.l << endl;
        return os;
    }

   private:
    int& r;  //a reference which require to be inititialized
    char c;
    int a;
    float b;
    double d;
    long l;
};

int main() {
    cout << Default::FromDefault();
    return 0;
}