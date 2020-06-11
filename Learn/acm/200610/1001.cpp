/*
 * File Created: Thursday, 11th June 2020 1:00:14 am
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Thursday, 11th June 2020 4:06:44 pm
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

    void preOrder() {
        if (root != nullptr) {
            cout << root->data;
            doPreOrder(root->left);
            doPreOrder(root->right);
        }
        cout << endl;
    }

private:
    BNode<T> *root;
    void doPreOrder(BNode<T> *tree) {
        if (tree != nullptr) {
            cout << " " << tree->data;
            doPreOrder(tree->left);
            doPreOrder(tree->right);
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
    btree.preOrder();
}

int main() {
    // TestBinaryTree();

    int n;
    while (cin >> n) {
        BinaryTree<int> btree;
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            btree.insert(val);
        }
        btree.preOrder();
    }
    return 0;
}