/*
 * File Created: Friday, 12th June 2020 11:10:17 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Friday, 12th June 2020 11:44:20 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

class QueryResult;

class TextQuery {
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;

private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream& is) : file(new vector<string>) {
    string text;
    while (getline(is, text)) {
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word) {
            auto& lines = wm[word];
            if (!lines) {
                lines.reset(new set<line_no>);
            }
            lines->insert(n);
        }
    }
}

class QueryResult {
    friend ostream& print(ostream&, const QueryResult&);

public:
    QueryResult(string s,
                shared_ptr<set<TextQuery::line_no>> p,
                shared_ptr<vector<string>> f)
        : sought(s), lines(p), file(f) {}

private:
    string sought;
    shared_ptr<vector<string>> file;
    shared_ptr<set<TextQuery::line_no>> lines;
};

QueryResult
TextQuery::query(const string& sought) const {
    static shared_ptr<set<line_no>> nodata(new set<line_no>);

    auto loc = wm.find(sought);
    if (loc == wm.end()) {
        return QueryResult(sought, nodata, file);
    } else {
        return QueryResult(sought, loc->second, file);
    }
}

inline string make_plural(size_t times, string word, string suffix) {
    return times > 1 ? word + suffix : word;
}

ostream& print(ostream& os, const QueryResult& qr) {
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;

    for (auto num : *qr.lines) {
        os << "\t(line " << num + 1 << ") " << qr.file->at(num) << endl;
    }
    return os;
}

void runQueris(ifstream& infile) {
    TextQuery tq(infile);
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main() {
    while (true) {
        cout << "enter filepath to query, or q to quit: ";
        string path;
        if (!(cin >> path) || path == "q") break;
        ifstream fin;
        fin.open(path);
        if (!fin.is_open()) {
            cout << "fail to open: " << path << endl;
        } else {
            runQueris(fin);
            fin.close();
        }
    }
}
