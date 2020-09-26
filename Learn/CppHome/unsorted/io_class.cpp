
#include <iostream>

using namespace std;

class Student {
   public:
    friend istream& operator>>(istream& is, Student& s) {
        is >> s.no >> s.score;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.no << " " << s.score;
        return os;
    }

   private:
    int no;
    double score;
};

int main() {
    Student sts[5];
    Student* ps = sts;
    for (int i = 0; i < 5; i++) {
        cin >> sts[i];
    }
    for (int i = 0; i < 3; i++) {
        cout << *ps << endl;
        ps += 2;
    }

    return 0;
}
