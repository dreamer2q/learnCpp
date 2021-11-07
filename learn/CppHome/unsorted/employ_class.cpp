
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Employee {
   public:
    Employee(int num, string na, string se, double w) : no(num), name(na), sex(se), wage(w) {
        count++;
        totalWage += wage;
    }
    void ShowBase() const {
        cout << "个人基本信息：" << endl
             << "编号：" << no << endl
             << "姓名：" << name << endl
             << "性别：" << sex << endl
             << "工资：" << wage << endl;
    }
    static void ShowStatic() {
        cout << "人数：" << Employee::count << endl
             << "总工资：" << Employee::totalWage << "元" << endl;
    }

   private:
    int no;
    string name;
    string sex;
    double wage;

    static int count;
    static double totalWage;
};
int Employee::count = 0;
double Employee::totalWage = 0;

int main() {
    vector<Employee> eps;
    int n;
    cin >> n;
    while (n--) {
        int num;
        double wage;
        string name, sex;
        cin >> num >> name >> sex >> wage;
        Employee tmp(num, name, sex, wage);
        eps.push_back(tmp);
    }
    Employee::ShowStatic();

    for (int i = 0; i < eps.size(); i++) {
        eps[i].ShowBase();
        cout << endl;
    }

    return 0;
}