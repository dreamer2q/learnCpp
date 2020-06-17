/*
 * File Created: Wednesday, 17th June 2020 6:37:26 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 17th June 2020 6:54:52 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

class Student {
public:
    static Student From(istream& is) {
        string n;
        int a;
        double s;
        is >> n >> a >> s;
        return Student(n, a, s);
    }
    Student(string n, int a, double s) : name(n), age(a), score(s) {}

    friend bool operator<(const Student& lhs, const Student& rhs) {
        if (fabs(lhs.score - rhs.score) < 1e-6) {
            if (lhs.age == rhs.age)
                return lhs.name < rhs.name;
            return lhs.age < rhs.age;
        }
        return lhs.score > rhs.score;
    }

    void display() const {
        printf("%s %d %0.2lf", name.c_str(), age, score);
    }

private:
    string name;
    int age;
    double score;
};

int main() {
    int n;
    while (cin >> n) {
        vector<Student> vs;
        for (int i = 0; i < n; i++) {
            vs.push_back(Student::From(cin));
        }
        sort(vs.begin(), vs.end());
        for (int i = 0; i < n; i++) {
            vs[i].display();
            // if (i != n - 1) {
            cout << endl;
            // }
        }
        // for_each(vs.begin(), vs.end(), [](const Student& s) {
        // s.display();
        // });
    }
    return 0;
}