
#include <iostream>
#include <string>

using namespace std;

typedef string Type;

Type initVal() {
    return "init val";
}

class Exercise {
   public:
    typedef double Type;

    Type setVal(Type);
    Type initVal();

   private:
    int val;
};

Exercise::Type Exercise::setVal(Type parm) {
    val = parm + initVal();
    cout << val << endl;
    return val;
}

Exercise::Type Exercise::initVal() {
    return 0.1;
};

int main() {
    Exercise e;
    e.setVal(111);
}
