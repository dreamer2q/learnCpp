#include <bits/stdc++.h>
using namespace std;

struct Student {
    int no;
    int age;
};

int cmpStudent(const void* a, const void* b) {
    Student* stuA = (Student*)a;
    Student* stuB = (Student*)b;
    if (stuA->age == stuB->age) {
        return stuA->no - stuB->no;
    }
    return stuA->age - stuB->age;
}

// template <typename T>
// T max(T a, T b) {
//     if (a > b) return a;
//     return b;
// }

int main() {
    vector<int> lst = {1, 2, 3};
    list<int> lst2 = {1, 2, 3};
    list<string> lst3 = {"123", "abc"};

    int* pInt;
    void* pVoid;

    int a = 1;
    pInt = &a;
    pVoid = &a;

    Student students[100];

    for (int i = 0; i < 100; i++) {
        auto item = students[i];
        if (item.age >= 5) {
            /// do sth you like
        }
    }

    qsort(students, 100, sizeof(Student), cmpStudent);

    return 0;
}
