#include <iostream>
#include <ncurses.h>
#include "../include/Game.h"


int main() {
  game_space::Game game(45, 125);
  game.start();
//  initscr();
//  printw("Hello, world!\n");
//  refresh();
//  getch();
//  endwin();
  return 0;
}