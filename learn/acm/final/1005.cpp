/*
 * File Created: Thursday, 11th June 2020 1:00:14 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Wednesday, 24th June 2020 6:57:55 pm
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
        BNode<T> *p = root, *p2;
        BNode<T> *newNode = new BNode<T>{
            data : data,
            left : nullptr,
            right : nullptr,
        };
        while (p != nullptr) {
            p2 = p;
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
            }
        }
    }

    vector<T> out;
    void levelOut() {
        deque<BNode<T> *> data;
        out.push_back(root->data);
        data.push_back(root);
        while (!data.empty()) {
            BNode<T> *d = data.front();
            data.pop_front();
            if (d->left) {
                out.push_back(d->left->data);
                data.push_back(d->left);
            }
            if (d->right) {
                out.push_back(d->right->data);
                data.push_back(d->right);
            }
        }
    }

private:
    BNode<T> *root;
    void doDelete(BNode<T> *tree) {
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
}

int main() {
    int n;
    while (cin >> n) {
        BinaryTree<int> btree;
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            btree.insert(val);
        }
        btree.levelOut();
        ostream_iterator<int> out(cout, " ");
        copy(btree.out.begin(), btree.out.end(), out);
        cout << endl;
    }
    return 0;
}
