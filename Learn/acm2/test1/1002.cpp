
#include <bits/stdc++.h>

using namespace std;

struct Student {
    string name;
    int age;
    double score;
};

int main() {
    while (1) {
        int t;
        vector<Student> stu;
        cin >> t;
        if (t <= 0) break;
        while (t--) {
            string name;
            int age;
            double score;
            cin >> name >> age >> score;
            stu.push_back({
                name,
                age,
                score,
            });
        }

        sort(stu.begin(), stu.end(), [](const Student& a, const Student& b) {
            if (fabs(a.score - b.score) < 1e-6) {
                if (a.age == b.age) return a.name < b.name;
                return a.age < b.age;
            }
            return a.score > b.score;
        });

        for (const auto& s : stu) {
            printf("%s %d %.2lf\n", s.name.c_str(), s.age, s.score);
        }
    }
    return 0;
}