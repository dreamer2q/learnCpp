
#ifndef __SCREEN_HEADER_H
#define __SCREEN_HEADER_H

#include <iostream>
#include <vector>

class Screen {
   public:
    //typedef std::string::size_type pos;
    using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}

    Screen& set(char c);
    Screen& set(pos r, pos col, char ch);
    char get() const { return contents[cursor]; }
    inline char get(pos ht, pos wd) const;

    Screen& move(pos r, pos c);

    Screen& display(std::ostream& os) {
        do_display(os);
        return *this;
    }
    const Screen& display(std::ostream& os) const {
        do_display(os);
        return *this;
    }

   private:
    void do_display(std::ostream& os) const;

    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};

class Window_mgr {
   private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

#endif