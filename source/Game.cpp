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

  game_state_ = ui::LOADING;
  loading_ = ui::Loading();
  main_menu_ = ui::MainMenu();
  map_ = map::Map();
  map_.loadMap();

}

void game_space::Game::start() {
  int key = -1;
  game_state_ = loading_.update(key);

  while (game_state_ != ui::EXIT) {
    key = getch();
    switch (game_state_) {
      case ui::LOADING:loading_.update(key);
        break;
      case ui::MAIN_MENU:main_menu_.update(key);
        break;
      case ui::GAME_FIELD:break;
      case ui::SETTINGS:break;
      case ui::EXIT:finish();
        break;
    }
  }
}

void game_space::Game::finish() {
  endwin();
}

