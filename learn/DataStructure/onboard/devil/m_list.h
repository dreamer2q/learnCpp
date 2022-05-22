#ifndef __M_LIST__
#define __M_LIST__

template <typename T>
struct MyNode {
    T data;        //数据
    MyNode* prev;  //上一个节点
    MyNode* next;  //下一个节点
};

template <typename T>
class MyListIterator {
   public:
    MyListIterator(MyNode<T>* node) : iter(node) {}

    //后缀++
    MyListIterator operator++(int) {
        auto tmp = *this;
        iter = iter->next;
        return tmp;
    }

    T& operator*() {
        return iter->data;
    }

    bool operator==(const MyListIterator& i) {
        return iter == i.iter;
    }
    bool operator!=(const MyListIterator& i) {
        return !(*this == i);
    }

   private:
    MyNode<T>* iter;  //迭代节点
};

template <typename T>
class MyList {
   private:
    MyNode<T>* root;  //哨兵节点
    MyNode<T>* tail;  //尾部节点

   public:
    MyList() {
        root = tail = new MyNode<T>;
        root->next = nullptr;
    };
    ~MyList() {
        while (root) {
            auto tmp = root->next;
            root = root->next;
            delete tmp;
        }
    };

    bool empty() { return root == tail; }

    MyListIterator<T> begin() const { return MyListIterator<T>(root->next); }
    MyListIterator<T> end() const { return MyListIterator<T>(nullptr); }

    const T& back() { return tail->data; }
    void push_back(const T& item) {
        auto newItem = new MyNode<T>{item, tail, nullptr};
        if (empty()) {
            root->next = newItem;
        }
        tail->next = newItem;
        tail = newItem;
    }
    void pop_back() {
        auto tmp = tail;
        tail = tail->prev;
        delete tmp;
    }
};

// 测试函数
// void test_list() {
//     MyList<char> lst;
//     for (int i = 'a'; i < 'z'; i++) {
//         lst.push_back(i);
//     }
//     for (auto it = lst.begin(); it != lst.end(); it++) {
//         cout << *it << " ";
//     }
//     cout << endl;
//     while (!lst.empty()) {
//         cout << lst.back() << " ";
//         lst.pop_back();
//     }
//     cout << endl;
// }

#endif
