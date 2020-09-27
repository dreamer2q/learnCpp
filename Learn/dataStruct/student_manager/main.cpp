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

/**
 *  A simple implementation of stack
 */
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

    void push(const T &item) {
        data[++pos] = item;
    }
    T topAndPop() { return data[pos--]; }
    T top() const { return data[pos]; }
    void pop() { pos--; }

   private:
    int pos;
    int m_size;
    T *data;
};

class Student {
    friend class Manager;

   public:
    static Student From(istream &is) {
        string no, name, _class, major;
        getchar();
        cout << "no: ";
        getline(is, no);
        cout << "name: ";
        getline(is, name);
        cout << "class: ";
        getline(is, _class);
        cout << "major: ";
        getline(is, major);
        return Student(no, name, _class, major);
    }
    Student(){};
    Student(string no, string name, string _class, string major) : name(name), no(no), m_class(_class), major(major) {}

    string getBy(string property) const {
        if (property == "name") return name;
        if (property == "no") return no;
        if (property == "class") return m_class;
        if (property == "major") return major;
        return "";
    }

    friend bool operator==(const Student &lhs, const Student &rhs);

   private:
    string name;
    string no;
    string m_class;
    string major;
};

bool operator==(const Student &lhs, const Student &rhs) {
    return lhs.no == rhs.no && lhs.name == rhs.name;
}
bool operator!=(const Student &lhs, const Student &rhs) {
    return !(lhs == rhs);
}

class Manager {
   public:
    Manager() : undoStack(10) {
        students.insertBack(Student("19051816", "Jack Li", "19052318", "Computer Science"));
        students.insertBack(Student("19051817", "Mary Wang", "19052318", "Software Engineering"));
        students.insertBack(Student("19051818", "Micheal", "19052318", "Computer Science"));
    }

    void list() {
        displayHeader();
        for (auto it = students.begin(); it != students.end(); it = it->next) {
            display(**it);
        }
    }
    Student *find(string property, string condition) {
        auto it = m_find(property, condition);
        if (it == nullptr) {
            cout << "not found with "
                 << property << " = " << condition
                 << endl;
        } else {
            displayHeader();
            display(*it);
        }
        return it;
    }

    void add() {
        displayHeader();
        auto stu = Student::From(cin);
        students.insertBack(stu);
        cout << "add a new student" << endl;
    }

    void edit(string no) {
        auto it = find("no", no);
        if (it != nullptr) {
            string item;
            getchar();
            cout << "new name: ";
            getline(cin, item);
            if (item != "") it->name = item;

            cout << "new class: ";
            getline(cin, item);
            if (item != "") it->m_class = item;

            cout << "new major: ";
            getline(cin, item);
            if (item != "") it->major = item;

            display(*it);
            cout << "update finished" << endl;
        }
    }

    void remove(string no) {
        auto it = find("no", no);
        if (it != nullptr) {
            bool ret = remove(*it);
            cout << "remove " << (ret ? "finished" : "failed") << endl;
        }
    }

    void undo() {
        if (undoStack.empty()) {
            cout << "undo stack is empty, remove first" << endl;
            return;
        }
        auto stu = undoStack.top();
        displayHeader();
        display(stu);
        cout << "are you sure you want to undo remove? (y/n): ";
        string cmd;
        cin >> cmd;
        if (cmd == "y") {
            students.insertBack(stu);
            cout << "removed" << endl;
        } else {
            cout << "nothing happened" << endl;
        }
    }

   private:
    MyList<Student> students;
    MyStack<Student> undoStack;

    Student *m_find(string condition, string data) {
        for (auto it = students.begin(); it != students.end(); it = it->next) {
            if (it->data.getBy(condition) == data) {
                return &(it->data);
            }
        }
        return nullptr;
    }

    bool remove(Student &stu) {
        auto it = students.find(stu);
        if (it != nullptr) {
            undoStack.push(stu);
        }
        return students.remove(it) != nullptr;
    }

    void displayHeader() {
        cout << "No.\t\tName\t\tClass\t\tMajor" << endl;
    }
    void display(const Student &s) {
        cout << s.no << " \t"
             << s.name << " \t"
             << s.m_class << " \t"
             << s.major << endl;
    }
};

void showWelcome() {
    cout << "\n\n\tWelcome to HDU Students Manager\n\n"
         << endl;
}
void showHelp() {
    cout << "help - show this message\n"
         << "add - add a new student\n"
         << "list - list all students\n"
         << "find [property] [condition] - find a student which matches @property == @condition\n"
         << "edit [no] - edit a student's information\n"
         << "remove [no] - remove a student by no"
         << "undo - undo remove operation\n"
         << "exit - exit this program\n";
}
void prompt() {
    cout << "> ";
}

Manager manager;
void readCmd() {
    string cmd, arg1, arg2;
    cin >> cmd;
    if (cmd == "help")
        showHelp();
    else if (cmd == "add") {
        manager.add();
    } else if (cmd == "find") {
        cin >> arg1 >> arg2;
        manager.find(arg1, arg2);
    } else if (cmd == "list") {
        manager.list();
    } else if (cmd == "edit") {
        cin >> arg1;
        manager.edit(arg1);
    } else if (cmd == "remove") {
        cin >> arg1;
        manager.remove(arg1);
    } else if (cmd == "undo") {
        manager.undo();
    } else if (cmd == "exit") {
        exit(0);
    } else {
        cout << "unkonw command: " << cmd << endl;
        cout << "type help for more information" << endl;
    }
}

int main() {
    showWelcome();
    showHelp();
    while (1) {
        prompt();
        readCmd();
    }
    return 0;
}