#include <string.h>

#include <iostream>

class Student {
   public:
    Student(const char* name, int age, int number) : m_number(number), m_age(age) {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    }
    Student() {
    }

   private:
    int m_number;
    int m_age;
    char* m_name;
};