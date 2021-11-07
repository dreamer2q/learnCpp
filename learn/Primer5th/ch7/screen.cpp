
#include "screen.h"

Screen& Screen::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}

Screen& Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}
Screen& Screen::set(pos r, pos col, char ch) {
    contents[r * width + col] = ch;
    return *this;
}

char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row + c];
}

void Screen::do_display(std::ostream& os) const {
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            os << contents[i * width + j];
        }
        os << "\n";
    }
    os << std::endl;
}
