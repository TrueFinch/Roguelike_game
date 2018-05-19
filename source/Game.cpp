//
// Created by truefinch on 17.05.18.
//


#include <ncurses.h>
#include "../include/Game.h"

game_space::Game::Game(int rows, int cols) : rows_{rows}, cols_{cols} {
  initscr();
  clear();
  keypad(stdscr, true);
  noecho();
  curs_set(0);
  resize_term(rows, cols);
}

void game_space::Game::start() {
  int key = -1;
  game_state = main_menu_.update(key);

  while (true) {
    key = getch();
    if (key == KEY_ESC) {
      break;
    }
    main_menu_.update(key);
  }
  finish();
}

void game_space::Game::finish() {
  endwin();
}

