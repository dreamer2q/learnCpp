#include <bits/stdc++.h>

using namespace std;

string replace(string line, string o, string n) {
  auto i = line.find(o);
  if (i != string::npos) {
    return line.replace(i, o.length(), n);
  }
  return line;
}

int main() {
  string line;
  cout << "> ";
  while (getline(cin, line)) {
    line = replace(line, "��", "��");
    line = replace(line, "��", "");
    line = replace(line, "?", "");
    line = replace(line, "��", "");
    cout << line << endl;
    cout << "> ";
  }
}
