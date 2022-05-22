#ifndef __CycleLinkList__
#define __CycleLinkList__

#include <bits/stdc++.h>

///遍历回调函数
template <typename T>
using VisitCallback = void(T&);

///链表节点内容
template <typename T>
struct LNode {
    T data;       //储存节点数据
    LNode* next;  //指向下一个节点
};

//前置声明
template <typename T>
class CycleList;

//链表迭代器, 用于迭代循环链表
template <typename T>
class CycleListIterator {
    friend class CycleList<T>;

   public:
    //构造函数，用于生成迭代器
    CycleListIterator(LNode<T>* current, LNode<T>* last) : curr(current), head(current) {
        _hasStarted = (current == last);
        prev = last;
    }

    //迭代器步进
    void next(unsigned steps = 1) {
        while (steps != 0) {
            prev = curr;
            curr = curr->next;
            steps--;
            _hasStarted = true;
        }
    }

    //重载+=运算符, 步进steps个元素
    CycleListIterator<T>& operator+=(const unsigned steps) {
        next(steps);
        return *this;
    }

    //重载++运算符，步进一个元素
    CycleListIterator<T>& operator++(int) {
        next(1);
        return *this;
    }

    //迭代器比较，用于判断是否迭代到终点
    bool operator==(const CycleListIterator<T>& iter) const {
        return _hasStarted == iter._hasStarted && curr == iter.curr;
    }
    //同上
    bool operator!=(const CycleListIterator<T>& iter) const {
        return !(*this == iter);
    }

    //获取迭代器所指向的内容
    T& operator*() {
        return curr->data;
    }

   private:
    //迭代器持有的私有元素
    LNode<T>* curr;    //指向当前的元素
    LNode<T>* head;    //指向头元素
    LNode<T>* prev;    //指向curr的前一个元素
    bool _hasStarted;  //迭代器是否开始
};

//循环链表
template <typename T>
class CycleList {
   public:
    //构造函数，生成一个空的链表
    CycleList() {
        tail = head = nullptr;
    }
    //析构函数，用于释放链表内的元素
    ~CycleList() {
        if (empty()) return;
        LNode<T>* p = head;
        while (p != tail) {
            LNode<T>* it = p;
            p = p->next;
            delete it;
        }
    }
    //获取首迭代器
    CycleListIterator<T> begin() { return CycleListIterator<T>(head, tail); }
    //获取尾巴迭代器
    CycleListIterator<T> end() { return CycleListIterator<T>(head, head); }

    //检查链表是否为空
    bool empty() { return head == nullptr; }
    //获取链表的长度
    size_t length() {
        if (empty()) return 0;
        size_t len = 1;
        LNode<T>* p = head;
        while (p != tail) {
            p = p->next;
            len++;
        }
        return len;
    }
    //获取链表第index个元素的内容
    T& at(unsigned index) {
        if (empty()) return T{};
        LNode<T>* p = _at(index);
        return p->data;
    }
    //在指定位置插入一个元素，默认是在头位置
    bool insert(const T& item, unsigned index = 0) {
        LNode<T>* newItem = new LNode<T>{item};
        if (empty()) {
            head = tail = newItem;
            return true;
        }
        if (index == 0) {
            newItem->next = head;
            head = newItem;
            tail->next = head;
            return true;
        }
        LNode<T>* p = _at(index - 1);
        newItem->next = p->next;
        p->next = newItem;
        return true;
    }

    //向末尾插入一个元素
    void push_back(const T& item) {
        LNode<T>* newItem = new LNode<T>{item};
        if (empty()) {
            head = tail = newItem;
            return;
        }
        newItem->next = head;
        tail->next = newItem;
        tail = newItem;
    }

    //移除迭代器所指向的元素
    bool remove(CycleListIterator<T>& iter) {
        if (empty()) return false;
        LNode<T>* pcur = iter.curr;
        if (iter.curr == iter.curr->next) {  //only one item
            head = tail = nullptr;
            iter.curr = nullptr;
            iter.head = nullptr;
        } else {  // more than one item
            if (iter.curr == head) {
                head = iter.curr->next;
            }
            iter.curr = iter.curr->next;
            iter.prev->next = iter.curr;
        }
        delete pcur;
        return true;
    }

    //移除指定位置的元素
    bool remove(unsigned index = 0) {
        if (empty()) return false;
        if (index == 0) {
            LNode<T>* p = head;
            head = head->next;
            tail->next = head;
            delete p;
            return true;
        }
        LNode<T>* p = _at(index - 1);
        LNode<T>* t = p->next;
        p->next = t->next;
        delete t;
        return true;
    }

    //获取元素所在的位置，没找到为-1
    int index(const T& item) {
        if (empty()) return -1;
        int i = 0;
        LNode<T>* p = head;
        while (p != tail) {
            p = p->next;
            i++;
        }
        return i;
    }

    //遍历整个链表
    void visit(VisitCallback<T> callback) {
        if (empty()) return;
        LNode<T>* p = head;
        callback(p->data);
        while (p != tail) {
            p = p->next;
            callback(p->data);
        }
    }

   private:
    //私有成员，私有方法
    LNode<T>* tail;  //链表尾指针
    LNode<T>* head;  //链表头指针

    //私有，获取特定位置的链表制作
    LNode<T>* _at(unsigned index) {
        if (empty()) return nullptr;
        LNode<T>* p = head;
        while (index != 0) {
            p = p->next;
            index--;
        }
        return p;
    }
};

//链表测试函数，用于测试链表的正确性
using std::cout;
using std::endl;
void test_cycle_list() {
    auto callback = [](int& i) {
        cout << i << ", ";
    };
    CycleList<int> list;
    list.insert(1);
    list.push_back(2);
    list.insert(3, 1);
    list.push_back(4);
    list.remove();
    list.visit(callback);
    cout << endl;

    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }

    for (auto it = list.begin(); it != list.end();) {
        cout << *it << ", ";
        list.remove(it);
    }
    cout << endl;
}

#endif
