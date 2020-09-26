/*
 * File Created: Tuesday, 16th June 2020 8:30:05 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Tuesday, 16th June 2020 8:42:45 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

void check(fstream& f, string file) {
    if (f.fail()) {
        cerr << "Open file " << file << " failed" << endl;
        exit(-1);
    }
}

void do_addline(fstream& fin, fstream& fout) {
    string line;
    unsigned no = 0;
    while (getline(fin, line)) {
        fout << setiosflags(ios_base::left) << setw(6) << ++no << line << endl;
    }
}

int main() {
    string infile, outfile;
    cout << "Input input filename: ";
    cin >> infile;
    cout << "Input output filename: ";
    cin >> outfile;

    fstream fin, fout;
    fin.open(infile, ios_base::in);
    check(fin, infile);
    fout.open(outfile, ios_base::out);
    check(fout, outfile);

    do_addline(fin, fout);

    fin.close();
    fout.close();
    return 0;
}