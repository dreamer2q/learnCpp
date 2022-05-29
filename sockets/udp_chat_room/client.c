#include <stdio.h>
#include <ncurses.h>

int main() {
  initscr();

  move(10, 10);

  printw("COLS: %d, LINES: %d", COLS, LINES);
  refresh();
  getch();

  endwin();
  return 0;
}
