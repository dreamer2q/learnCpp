
#include <iostream>
#include <string>

using namespace std;

class Tree {
   public:
    Tree() = default;
    Tree(int age) : age(age) {}

    void grow(int ages) {
        age += ages;
    }
    int getAge() {
        return age;
    }
    void showAge() {
        cout << "Age: " << getAge() << endl;
    }

   private:
    int age;
};

int main() {
    Tree dreamer(0);

    for (int i = 1; i < 10; i++) {
        cout << i << (i > 1 ? " years" : " year")
             << " later" << endl;
        _sleep(1000);
        dreamer.grow(1);
    }
    cout << "the tree of dreamer is now " << dreamer.getAge() << " years old" << endl;

    return 0;
}