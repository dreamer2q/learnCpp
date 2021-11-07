/*
 * File Created: Friday, 29th May 2020 11:28:47 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Saturday, 30th May 2020 12:19:34 am
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
class Node {
private:
    Node<T> *next;

public:
    T data;
    Node(const T &item, Node<T> *next = nullptr);
    void insertAfter(Node<T> *p);
    Node<T> *deleteAfter();
    const Node<T> *nextNode() const;
    Node<T> *&nextNode();
};

//默认参数写在声明里面即可，定义的时候就不需要了。
template <class T>
Node<T>::Node(const T &data, Node<T> *next) : data(data), next(next) {}

template <class T>
Node<T> *&Node<T>::nextNode() {
    return next;
}

template <class T>
const Node<T> *Node<T>::nextNode() const {
    return next;
}

template <class T>
void Node<T>::insertAfter(Node<T> *p) {
    p->next = next;
    next = p;
}

template <class T>
Node<T> *Node<T>::deleteAfter(void) {
    Node<T> *tempPtr = next;
    //不要使用0来表示空指针
    if (next == nullptr)
        return nullptr;
    next = tempPtr->next;

    return tempPtr;
}

//define LinkedList
template <class T>
class MyList {
private:
    Node<T> *front, *rear;
    Node<T> *prevPtr, *currPtr;
    int size;
    int position;

    Node<T> *newNode(const T &item, Node<T> *ptrNext = NULL) { return new Node<T>(item, ptrNext); }
    void freeNode(Node<T> *p) { delete p; }
    void copy(const MyList<T> &L);

public:
    MyList() : front(NULL), rear(NULL), prevPtr(NULL), currPtr(NULL) { size = position = 0; }
    MyList(const MyList<T> &L) { copy(L); }
    ~MyList() { clear(); }
    MyList<T> &operator=(const MyList<T> &L) {
        clear();
        copy(L);
        return *this;
    }
    int getSize() const { return size; }
    bool isEmpty() const { return (size == 0); }
    void reset(int pos = 0);
    void next();
    bool endOfList() const { return currPtr->nextNode() == NULL; }
    int currentPosition(void) const { return position; }
    void insertFront(const T &item);
    void insertRear(const T &item);
    //void insertAt(const T &item);
    void insertAfter(const T &item);
    T deleteFront();
    void deleteCurrent();
    T &data() { return currPtr->data; }
    const T &data() const { return currPtr->data; }
    void clear();
    void display() const;
};

template <class T>
void MyList<T>::clear() {
    Node<T> *tmp = NULL;
    while (front) {
        tmp = front;
        front = front->nextNode();
        freeNode(tmp);
    }

    front = rear = prevPtr = currPtr = NULL;
}

template <class T>
void MyList<T>::copy(const MyList<T> &L) {
    Node<T> *tmp = NULL, *prev = NULL, *cur = NULL;
    int pos = L.currentPosition();
    int i = 0;

    tmp = L.front;
    while (tmp) {
        cur = newNode(tmp->data);
        if (i == 0)
            front = cur;
        else {
            prev->insertAfter(cur);

            if (i == pos) {
                prevPtr = prev;
                currPtr = cur;
            }
        }

        prev = cur;
        rear = cur;
        tmp = tmp->nextNode();
        i++;
    }

    position = pos;
    size = L.size;
}

template <class T>
void MyList<T>::reset(int pos) {
    Node<T> *tmp = front;
    int i = 0;

    assert(pos >= 0 && pos < size);
    while (i <= pos) {
        if (i == 0)
            currPtr = prevPtr = tmp;
        else {
            prevPtr = currPtr;
            currPtr = tmp;
        }

        tmp = tmp->nextNode();
        i++;
    }

    position = pos;
}

template <class T>
T MyList<T>::deleteFront() {
    Node<T> *tmp = NULL;
    T res;
    assert(size > 0 || front);

    tmp = front;
    res = tmp->data;
    front = front->nextNode();
    freeNode(tmp);
    size -= 1;
    position = 0;

    return res;
}

template <class T>
void MyList<T>::deleteCurrent() {
    assert(currPtr);

    Node<T> *tmp = currPtr->nextNode();

    if (currPtr == front)
        deleteFront();
    else {
        freeNode(prevPtr->deleteAfter());
        currPtr = tmp;
    }
    size -= 1;
}

template <class T>
void MyList<T>::insertAfter(const T &item) {
    if (currPtr) {
        currPtr->insertAfter(newNode(item));
        prevPtr = currPtr;
        currPtr = currPtr->nextNode();
        position += 1;
    } else
        front = rear = currPtr = prevPtr = newNode(item);

    size += 1;
}

template <class T>
void MyList<T>::insertFront(const T &item) {
    Node<T> *tmp = front;
    Node<T> *newnode = newNode(item);

    newnode->nextNode() = front;
    if (front == NULL)
        rear = newnode;
    front = newnode;
    currPtr = front;
    prevPtr = front;
    size += 1;
    position = 0;
}

template <class T>
void MyList<T>::insertRear(const T &item) {
    Node<T> *newnode = newNode(item);

    if (rear) {
        rear->nextNode() = newnode;
        prevPtr = rear;
        rear = newnode;
    } else {
        rear = newnode;
        prevPtr = rear;
        front = rear;
    }

    currPtr = rear;

    size += 1;
    position = size - 1;
}

template <class T>
void MyList<T>::next() {
    assert(currPtr);

    if (currPtr->nextNode() == NULL) {
        cout << "This is last elem" << endl;
        return;
    } else {
        prevPtr = currPtr;
        currPtr = currPtr->nextNode();
        position += 1;
    }
}

template <class T>
void MyList<T>::display() const {
    Node<T> *tmp = front;

    if (front == NULL) {
        cout << "list is empty" << endl;
        return;
    }

    while (tmp) {
        cout << tmp->data << " ";
        tmp = tmp->nextNode();
    }
    cout << endl;
}

int main() {
    MyList<int> a, b;

    for (int i = 0; i < 5; i++) {
        a.insertAfter(i + 1);
        b.insertAfter(-i - 1);
    }
    b.reset();
    for (int i = 0; i < 5; i++) {
        a.insertAfter(b.data());
        b.next();
    }

    a.display();

    return 0;
}
