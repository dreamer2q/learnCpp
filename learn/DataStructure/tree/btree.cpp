#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BNode {
    T data;
    BNode<T> *left;
    BNode<T> *right;
    int count;
};

enum VisitType {
    PreOrder,
    InOrder,
    PostOrder,
};

///return true to break;
/// false to continue;
template <typename T>
using VisitCallback = bool(T &);

template <typename T>
class BTree {
   public:
    BTree() {
        root = nullptr;
    }
    ~BTree() {
        cout << "do delete tree" << endl;
    }

    void insert(const T &data) {
        auto *item = new BNode<T>{
            data : data,
            left : nullptr,
            right : nullptr,
            count : 0,
        };
        if (root == nullptr) {
            root = item;
        } else {
            doOrderInsert(root, item);
        }
    }

    bool empty() {
        return root == nullptr;
    }

    void traverse(VisitType type, VisitCallback<T> callback = nullptr) {
        doTraverse(root, type, callback);
    }

    void traverseNonRecursive(VisitType type, VisitCallback<T> callback) {
        switch (type) {
            case PreOrder:
                doPreTraverseNonRecursive(root, callback);
                break;
            case InOrder:
                doInTraverseNonRecursive(root, callback);
                break;
            case PostOrder:
                doPostTraverseNonRecursive(root, callback);
                break;
        }
    }

    ///nullptr if not found
    BNode<T> *find(const T &data) {
        return nullptr;
    }

   private:
    BNode<T> *root;

    void doTraverse(BNode<T> *node, VisitType type, VisitCallback<T> callback) {
        if (node != nullptr) {
            switch (type) {
                case PreOrder:
                    if (callback != nullptr && callback(node->data)) return;
                    doTraverse(node->left, type, callback);
                    doTraverse(node->right, type, callback);
                    break;
                case InOrder:
                    doTraverse(node->left, type, callback);
                    if (callback != nullptr && callback(node->data)) return;
                    doTraverse(node->right, type, callback);
                    break;
                case PostOrder:
                    doTraverse(node->left, type, callback);
                    doTraverse(node->right, type, callback);
                    if (callback != nullptr && callback(node->data)) return;
            }
        }
    }

    void doInTraverseNonRecursive(BNode<T> *node, VisitCallback<T> callback) {
        if (node == nullptr) return;
        stack<BNode<T> *> s;
        s.push(node);
        BNode<T> *p = nullptr;
        while (!s.empty()) {
            p = s.top();
            while (p) {
                p = p->left;
                s.push(p);
            }
            s.pop();  //pop nullptr pointer
            if (!s.empty()) {
                p = s.top();
                s.pop();
                if (callback && callback(p->data)) return;
                s.push(p->right);
            }
        }
    }
    void doPreTraverseNonRecursive(BNode<T> *node, VisitCallback<T> callback) {
        if (node == nullptr) return;
        stack<BNode<T> *> s;
        s.push(node);
        BNode<T> *p = nullptr;
        while (!s.empty()) {
            p = s.top();
            while (p) {
                if (callback != nullptr && callback(p->data)) return;
                p = p->left;
                s.push(p);
            }
            s.pop();  //pop nullptr pointer
            if (!s.empty()) {
                p = s.top();
                s.pop();
                s.push(p->right);
            }
        }
    }

    void doPostTraverseNonRecursive(BNode<T> *node, VisitCallback<T> callback) {
        if (node == nullptr) return;
        stack<BNode<T> *> s;
        s.push(node);
        BNode<T> *p = nullptr, *q = nullptr;
        while (!s.empty()) {
            p = s.top();
            while (p) {
                p = p->left;
                s.push(p);
            }
            s.pop();  //pop nullptr pointer
            if (!s.empty()) {
                p = s.top();
                if (p->right) {
                    s.push(p->right);
                } else {
                    if (callback != nullptr && callback(p->data)) return;
                    p = s.top();
                    s.pop();
                    if (!s.empty()) {
                        q = s.top();
                    }
                    while (q && q->right == p) {
                        if (callback != nullptr && callback(q->data)) return;
                        p = q;
                        s.pop();
                        q = nullptr;
                        if (!s.empty()) {
                            q = s.top();
                        }
                    }
                    s.push(nullptr);
                }
            }
        }
    }

    void doOrderInsert(BNode<T> *&node, BNode<T> *item) {
        if (node == nullptr) return;
        if (node->data < item->data) {
            if (node->left == nullptr) {
                node->left = item;
            } else {
                doOrderInsert(node->left, item);
            }
        } else if (node->data > item->data) {
            if (node->right == nullptr) {
                node->right = item;
            } else {
                doOrderInsert(node->right, item);
            }
        } else {
            // delete item;
            node->count++;
        }
    }
};

bool print(int &t) {
    cout << t << endl;
    return false;
}

void testBTree() {
    BTree<int> bt;

    bt.insert(5);
    bt.insert(2);
    bt.insert(4);
    bt.insert(10);
    for (int i = 0; i < 10; i++) {
        bt.insert(i + 1);
    }

    auto print = [](int &item) -> bool {
        cout << item << " ";
        return false;
    };

    cout << "\n-----PreOrder-------" << endl;
    bt.traverse(PreOrder, print);
    cout << endl;
    bt.traverseNonRecursive(PreOrder, print);

    cout << "\n-------InOrder-------" << endl;
    bt.traverse(InOrder, print);
    cout << endl;
    bt.traverseNonRecursive(InOrder, print);

    cout << "\n------PostOrder-------" << endl;
    bt.traverse(PostOrder, print);
    cout << endl;
    bt.traverseNonRecursive(PostOrder, print);
    cout << endl;
}

int main() {
    testBTree();
    return 0;
}
