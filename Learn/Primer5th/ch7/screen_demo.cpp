
#include <conio.h>

#include <iostream>

#include "screen.h"

using namespace std;

int main() {
    Screen myScreen(10, 30, 'X');
    Screen::pos x = 0, y = 0;
    myScreen.set('#');
    myScreen.display(cout);
    char ch;
    while (1) {
        if (kbhit()) {
            ch = getch();
            switch (ch) {
                case 'h':
                    x--;
                    break;
                case 'j':
                    y++;
                    break;
                case 'k':
                    y--;
                    break;
                case 'l':
                    x++;
                    break;
                default:
                    continue;
            }
            myScreen.move(y, x);
            myScreen.set('#');
            myScreen.display(cout);
        }
    }
}
