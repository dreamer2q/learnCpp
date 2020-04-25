#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct MatchItem {
    char nums[4];
    int cnt, pos;
    friend istream& operator>>(istream& is, MatchItem& m) {
        int tmp;
        is >> tmp >> m.cnt >> m.pos;
        for (auto& n : m.nums) {
            n = tmp % 10;
            tmp /= 10;
        }
        return is;
    }

    bool match(int cand) const {
        int c = 0, p = 0;
        bool vis[4] = {false};
        for (int i = 0; i < 4; i++) {
            int t = cand % 10;
            if (t == nums[i])
                p++;
            for (int j = 0; j < 4; j++) {
                if (!vis[j] && t == nums[j]) {
                    vis[j] = true;
                    c++;
                    break;
                }
            }
            cand /= 10;
        }
        return c == cnt && p == pos;
    }
};

void testItem() {
    MatchItem item;
    string s = "4815 2 1";
    stringstream strIn;
    strIn.str(s);
    strIn >> item;
    cout << item.match(4560);
}

int main() {
    //    testItem();
    int cas;
    while (cin >> cas) {
        if (cas == 0) break;
        vector<MatchItem> v;
        while (cas--) {
            MatchItem item;
            cin >> item;
            v.push_back(item);
        }
        int ans = 0;
        int candidates = 0;
        for (int i = 1000; i <= 9999; i++) {
            bool flag = true;
            for (const auto& item : v) {
                if (item.match(i))
                    continue;
                flag = false;
                break;
            }
            if (flag) {
                ans = i;
                candidates++;
                if (candidates > 1)
                    break;
            }
        }
        if (candidates > 1)
            cout << "Not sure" << endl;
        else
            cout << ans << endl;
    }

    return 0;
}