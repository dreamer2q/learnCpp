
#include <iostream>

using namespace std;

struct time {
    int year, month, day, hour, minute, second;
    iostream& operator<<(iostream& out) {
        out << year << '-' << month << '-' << day << " " << hour << ":" << minute << ":" << second << endl;
        return out;
    }
    friend istream& operator>>(istream& in, time &t) {
        std::cout << "input year: ";
        in >> t.year;
        std::cout << "input month: ";
        in >> t.month;
        std::cout << "input day: ";
        in >> t.day;
        std::cout << "input hour: ";
        in >> t.hour;
        std::cout << "input minute: ";
        in >> t.minute;
        std::cout << "input second: ";
        in >> t.second;
        return in;
    }
    friend ostream& operator<<(ostream& out, time t) {
        out << t.year << "-" << t.month << "-" << t.day << " " << t.hour << ":" << t.minute << ":" << t.second << std::endl;
        return out;
    }
};

int main() {
    time t;
    cin >> t;
    cout << t;
    return 0;
}