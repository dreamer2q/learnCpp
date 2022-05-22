#ifndef __M_STACK__
#define __M_STACK__

template <typename T>
class MyStack {
    const size_t INIT_SIZE = 100;

   private:
    T* data;
    int m_size;
    int curr;

   public:
    MyStack() : curr(-1), m_size(INIT_SIZE) {
        data = new T[m_size];
    }
    ~MyStack() {
        if (data != nullptr) delete data;
    }

    int size() { return curr + 1; }
    T top() { return data[curr]; };
    void pop() { curr--; }
    void push(const T& item) {
        if (curr >= m_size - 1) {
            m_size = m_size * 2;
            auto* tmp = data;
            data = new T[m_size];
            for (int i = 0; i <= curr; i++) {
                data[i] = tmp[i];
            }
            delete tmp;
        }
        data[++curr] = item;
    }
};

#endif
