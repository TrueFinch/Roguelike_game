#include <iostream>
#include <ncurses.h>
#include "GameManager.h"

int main() {
  int max_rows, max_cols;
  getmaxyx(stdscr, max_rows, max_cols);
  game::GameManager& game = game::GameManager::Instance();
  game.init(max_rows, max_cols);
  game.Start();
  return 0;
}