
/** 
 *  THIS IS THE INTRODUCTION OF THE CODE
 * 
 * IN THIS CODE, A LINKEDLIST IS IMPLEMENTED AND HAS TEST FUNCTIONS WHICH ENSURE
 * THAT BASIC FEATURE IS OK BUT THEY HAVE THEIR OWN FEATURES SO USE IS WITH CAUTION.
 * 
 * ALSO, THE CODE ARE ONLY A PIECE OF HOMEWORK THAT MEETS MOST OF THE REQIUREMENTS.
 * 
 * BESIDES, A MIT LICENSE IS PROVIDED IN THIS REPO WHICH YOU CAN FOUND AT THE ROOT OF
 * THIS PROJECT.
 * 
 * CREATED BY DREAMER2Q AT 2020年9月26日
 */

#include <bits/stdc++.h>

using namespace std;

//define the struct used for LinkedList
template <typename T>
struct Node {
    T data;
    Node<T> *next;

    T operator*() {
        return data;
    }
};

//main implement for LinkedList
template <typename T>
class MyList {
   public:
    //new a space to store the head point
    MyList() : head(new Node<T>) { head->next = nullptr; }

    //remember to delete in case of memory leak
    ~MyList() {
        auto it = head->next;
        while (it) {
            auto tmp = it;
            it = it->next;
            delete tmp;
        }
        delete head;
    }

    //insert a @data typed T at back of the @pos,
    Node<T> *insert(Node<T> *pos, T data) {
        auto next = pos->next;
        auto item = new Node<T>{
            data : data,
            next : next,
        };
        pos->next = item;
        return item;
    }
    //insert a @data at the last position
    Node<T> *insertBack(T data) {
        return insert(_last(), data);
    }
    //insert a @data at a position that makes it ordered;
    Node<T> *insertOrdered(T data) {
        auto it = head;
        while (it->next && it->data < data) {
            it = it->next;
        }
        return insert(it, data);
    }
    //remove item after @pos
    Node<T> *remove(Node<T> *pos) {
        auto tmp = pos->next;
        if (tmp != nullptr) {
            pos->next = tmp->next;
            delete tmp;
        }
        return tmp;
    }
    //remove the item if it matched the @data
    //otherwise, do nothing with a nullptr return value.
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
    //find the item if it matches the @data
    //nullptr is returned if not found
    Node<T> *find(T data) {
        auto it = begin();
        while (it && it->data != data) {
            it = it->next;
        }
        return it;
    }
    //merge this with another LinkedList
    //and return a newly built LinkedList
    MyList<T> merge(MyList<T> &list) {
        MyList ret;
        for (auto it = this->begin(); it != this->end(); it = it->next) {
            ret.insertOrdered(**it);
        }
        for (auto it = list.begin(); it != list.end(); it = it->next) {
            ret.insertOrdered(**it);
        }
        return ret;
    }
    //return a newly built LinkedList with its nodes from back to forward
    MyList<T> reverse() {
        MyList<T> list;
        auto it = head->next;
        while (it) {
            list.insert(list.head, it->data);
            it = it->next;
        }
        return list;
    };

    //help function for convenience
    Node<T> *begin() { return head->next; }
    Node<T> *end() { return nullptr; }

    //calculate the total nodes
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

//help function to print all the item in LinkedLink with a prefix
template <typename T>
void printList(string prefix, MyList<T> &list) {
    cout << prefix << " = ";
    for (auto it = list.begin(); it != list.end(); it = it->next) {
        cout << **it << " ";
    }
    cout << endl;
}

//test function to ensure its corrective
void test() {
    MyList<int> list;
    for (int i = 0; i < 10; i++) {
        list.insertBack(i);
    }
    printList("list", list);

    MyList<int> list2;

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