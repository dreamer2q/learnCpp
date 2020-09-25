
#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;

    T operator*() {
        return data;
    }
};

template <typename T>
class LinkedList {
   public:
    LinkedList() : head(new Node<T>) { head->next = nullptr; }
    ~LinkedList() {
        auto it = head->next;
        while (it) {
            auto tmp = it;
            it = it->next;
            delete tmp;
        }
        delete head;
    }

    Node<T> *insert(Node<T> *pos, T data) {
        auto next = pos->next;
        auto item = new Node<T>{
            data : data,
            next : next,
        };
        pos->next = item;
        return item;
    }
    Node<T> *insertBack(T data) {
        return insert(_last(), data);
    }
    Node<T> *insertOrdered(T data) {
        auto it = head;
        while (it->next && it->data < data) {
            it = it->next;
        }
        return insert(it, data);
    }
    Node<T> *remove(Node<T> *pos) {
        auto tmp = pos->next;
        if (tmp != nullptr) {
            pos->next = tmp->next;
            delete tmp;
        }
        return tmp;
    }
    Node<T> *remove(T data) {
        auto it = head;
        while (it->next && it->next->data != data) {
            it = it->next;
        }
        if (it->next) {
            remove(it);
        }
        return it->next;
    }
    Node<T> *find(T data) {
        auto it = begin();
        while (it && it->data != data) {
            it = it->next;
        }
        return it;
    }

    LinkedList<T> merge(LinkedList<T> &list) {
        LinkedList ret;
        for (auto it = this->begin(); it != this->end(); it = it->next) {
            ret.insertOrdered(**it);
        }
        for (auto it = list.begin(); it != list.end(); it = it->next) {
            ret.insertOrdered(**it);
        }
        return ret;
    }

    LinkedList<T> reverse() {
        LinkedList<T> list;
        auto it = head->next;
        while (it) {
            list.insert(list.head, it->data);
            it = it->next;
        }
        return list;
    };

    Node<T> *begin() { return head->next; }
    Node<T> *end() { return nullptr; }

    size_t length() {
        size_t n = 0;
        auto it = head->next;
        while (it) {
            it = it->next;
            n++;
        }
        return n;
    }

   private:
    Node<T> *head;

    Node<T> *_last() {
        auto it = head;
        while (it->next) {
            it = it->next;
        }
        return it;
    }
};

template <typename T>
void printList(string prefix, LinkedList<T> &list) {
    cout << prefix << " = ";
    for (auto it = list.begin(); it != list.end(); it = it->next) {
        cout << **it << " ";
    }
    cout << endl;
}

void test() {
    LinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.insertBack(i);
    }
    printList("list", list);

    LinkedList<int> list2;

    for (int i = 10; i > 0; i--) {
        list2.insertBack(i);
    }
    printList("list2", list2);

    auto list3 = list.merge(list2);
    printList("list3", list3);

    auto list4 = list3.reverse();
    printList("list4", list4);
}

int main() {
    test();
}