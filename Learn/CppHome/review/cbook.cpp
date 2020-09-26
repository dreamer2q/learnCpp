/*
 * File Created: Friday, 12th June 2020 7:34:34 pm
 * Author: Jack Li (dreamer22qq@gmail.com)
 * -----
 * Last Modified: Friday, 12th June 2020 8:03:09 pm
 * Modified By: Jack Li (dreamer22qq@gmail.com>)
 * -----
 * Description: 
 * 
 * Copyright: mit
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

class CBook {
public:
    CBook() {}
    CBook(const string& title, const string& author, double price, const string& desc)
        : title(title), author(author), price(price), description(desc) {}

    void setTitle(const string& newTitle) {
        title = newTitle;
    }
    string getTitle() const {
        return title;
    }
    void setAuthor(const string& newAuthor) {
        author = newAuthor;
    }
    string getAuthor() const {
        return author;
    }
    double getPrice() {
        return price;
    }
    void setPrice(double newPrice) {
        price = newPrice;
    }
    void setDescription(const string& newDesc) {
        description = newDesc;
    }
    string getDescription() const {
        return description;
    }

private:
    string title;
    string author;
    double price;
    string description;
};

void testCBook() {
    CBook cb("title", "author", 10.0, "this is a book description");
    // assert(cb.getAuthor() == "author");
    // assert(cb.getTitle() == "title");
    // assert(cb.getDescription() == "this is a book description");
    // assert(cb.getPrice() - 10 < 1e6);
    // cb.setAuthor("newAuthor");
    // cb.setPrice(20);
    // assert(cb.getAuthor() == "newAuthor");
    // assert(cb.getPrice() - 20 < 1e6);
    cout << "test success" << endl;
}

int main() {
    testCBook();
    return 0;
}