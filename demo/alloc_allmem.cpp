#include <iostream>

using namespace std;

int main() {
  int i = 0;
  while (new char[1 << 10]) {
    i++;
  }
  cout << i << "MB" << endl;
}
