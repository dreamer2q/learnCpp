/**
 * 
 *  THIS IS A VERY SIMPLE IMPLEMENTATION OF STACK
 * THE BASE STORAGE IS AN ARRAY WHICH SHOULD BE INITIALIZED WITH A SIZE
 * THEN WITH A POSITION TO INDICATE THE CURRENT POSTION FOR OPERATITON OF
 * PUSH, TOP AND SO ON.
 * 
 */

#include <bits/stdc++.h>

using namespace std;

template <typename T>
class MyStack {
   public:
    MyStack(int size) : m_size(size), pos(0) {
        data = new T[size];
    }
    ~MyStack() {
        delete[] data;
    }

    size_t size() const { return pos; }

    bool empty() const { return pos == 0; }

    void push(const T& item) {
        data[++pos] = item;
    }
    T topAndPop() { return data[pos--]; }
    T top() const { return data[pos]; }
    void pop() { pos--; }

   private:
    int pos;
    int m_size;
    T* data;
};

void test() {
    MyStack<int> stack(100);
    int n = 10;
    for (int i = 0; i < n; i++) {
        stack.push(i);
    }
    cout << "stack = ";
    for (int i = 0; i < n; i++) {
        cout << stack.topAndPop() << " ";
    }
    cout << endl;
}
int main() {
    test();
}