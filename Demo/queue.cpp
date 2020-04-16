#include <iostream>
#include <queue>

using namespace std;

using ElementType = int;
using Tree = Node*;

struct Node {
    Tree left;
    Tree right;
    ElementType value;
};

Tree NewTree() {
    return new Node;
}

int main() {
    priority_queue<int> pq;
    pq.push(1);

    queue<int> q;
    q.push(1);
    q.push(3);
    q.push(4);
    q.pop();

    int e = q.empty();
    cout << q.size() << endl;
    cout << e << endl;
    cout << q.empty() << endl;

    return 0;
}