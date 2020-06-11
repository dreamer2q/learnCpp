/*
 * File Created: Thursday, 11th June 2020 3:58:00 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Thursday, 11th June 2020 4:26:52 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct BNode {
    T data;
    BNode<T> *left, *right;
};

template <class T>
class BinaryTree {
public:
    BinaryTree() {
        root = nullptr;
    };
    ~BinaryTree() {
        //释放内存空间 bfs
    }

    void insert(T data) {
        if (root == nullptr) {
            root = new BNode<T>{
                data : data,
                left : nullptr,
                right : nullptr,
            };
            return;
        }
        BNode<T> *p = root;
        BNode<T> *newNode = new BNode<T>{
            data : data,
            left : nullptr,
            right : nullptr,
        };
        while (p != nullptr) {
            if (data < p->data) {
                if (p->left == nullptr) {
                    p->left = newNode;
                    break;
                } else {
                    p = p->left;
                }
            } else if (data > p->data) {
                if (p->right == nullptr) {
                    p->right = newNode;
                    break;
                } else {
                    p = p->right;
                }
            } else {
                // break;
                //题目保证数据不会重复
                //不然就让它超时吧
            }
        }
    }

    vector<T> inOrder() {
        vector<T> out;
        if (root != nullptr) {
            doInOrder(root->left, out);
            out.push_back(root->data);
            doInOrder(root->right, out);
        }
        return out;
    }
    vector<T> preOrder() {
        vector<T> out;
        if (root != nullptr) {
            out.push_back(root->data);
            doPreOrder(root->left, out);
            doPreOrder(root->right, out);
        }
        return out;
    }

private:
    BNode<T> *root;
    void doInOrder(BNode<T> *tree, vector<T> &out) {
        if (tree != nullptr) {
            doInOrder(tree->left, out);
            out.push_back(tree->data);
            doInOrder(tree->right, out);
        }
    }
    void doPreOrder(BNode<T> *tree, vector<T> &out) {
        if (tree != nullptr) {
            out.push_back(tree->data);
            doPreOrder(tree->left, out);
            doPreOrder(tree->right, out);
        }
    }

    void doDelete(BNode<T> *tree) {
        //postOrder
        if (tree != nullptr) {
            doDelete(tree->left);
            doDelete(tree->right);
            delete tree;
        }
    }
};

void TestBinaryTree() {
    BinaryTree<int> btree;
    btree.insert(1);
    btree.insert(3);
    btree.insert(4);
    btree.insert(2);
    btree.inOrder();
}

int main() {
    int n;
    while (cin >> n && n) {
        cin.get();  //consume '\n'
        BinaryTree<char> bt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        char c;
        while (ss >> c) {
            bt.insert(c);
        }
        auto btPre = bt.preOrder();
        auto btIn = bt.inOrder();
        for (int i = 0; i < n; i++) {
            BinaryTree<char> bt2;
            getline(cin, line);
            ss.clear();
            ss.str(line);
            // ss.setf()
            while (ss >> c) {
                bt2.insert(c);
            }
            auto bt2Pre = bt2.preOrder();
            auto bt2In = bt2.inOrder();
            if (equal(btPre.begin(), btPre.end(), bt2Pre.begin()) &&
                equal(btIn.begin(), btIn.end(), bt2In.begin())) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}