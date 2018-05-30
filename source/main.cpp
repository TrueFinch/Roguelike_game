#include <iostream>
#include <ncurses.h>
#include "Game.h"

int main() {
  int max_rows, max_cols;
  getmaxyx(stdscr, max_rows, max_cols);
  game_space::Game game(max_rows, max_cols);
  game.start();
  return 0;
}