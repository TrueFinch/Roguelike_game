#include <iostream>
#include <ncurses.h>
#include "Game_manager.h"

int main() {
  int max_rows, max_cols;
  getmaxyx(stdscr, max_rows, max_cols);
  game::Game_manager game(max_rows, max_cols);
  game.start();
  return 0;
}