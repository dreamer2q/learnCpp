/*
 * File Created: Wednesday, 10th June 2020 8:26:39 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Thursday, 11th June 2020 12:17:37 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

void dfs(string preOrder, string inOrder) {
    auto root = inOrder.find(preOrder[0]);                     //寻找jj
    dfs(preOrder.substr(1, root), inOrder.substr(0, root));    //左子书
    dfs(preOrder.substr(root + 1), inOrder.substr(root + 1));  //右子树
    cout << inOrder[0];                                        //输出根
}

int find(const vector<int>& vec, int val) {
    int res = -1;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == val) {
            res = i;
            break;
        }
    }
    return res;
}

vector<int> ans;

void dfs(vector<int> preOrder, vector<int> inOrder) {
    if (preOrder.empty()) return;
    auto root = find(inOrder, preOrder[0]);

    //left subtree
    auto p = preOrder.begin();
    auto i = inOrder.begin();
    vector<int> leftPreOrder(p + 1, p + root + 1);
    vector<int> leftInOrder(i, i + root);
    dfs(leftPreOrder, leftInOrder);
    //right subtree
    vector<int> rightPreOrder(p + root + 1, preOrder.end());
    vector<int> rightInOrder(i + root + 1, inOrder.end());
    dfs(rightPreOrder, rightInOrder);
    //output root value -> postOrder
    // cout << preOrder[0] << " ";
    ans.push_back(preOrder[0]);
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<int> preOrder, inOrder;
        for (int i = 0; i < n; i++) {
            int value;
            cin >> value;
            preOrder.push_back(value);
        }
        for (int i = 0; i < n; i++) {
            int value;
            cin >> value;
            inOrder.push_back(value);
        }
        ans.clear();
        dfs(preOrder, inOrder);
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
            if (i != ans.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
