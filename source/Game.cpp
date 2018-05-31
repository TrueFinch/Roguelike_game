//
// Created by truefinch on 17.05.18.
//


#include <ncurses.h>
#include "../include/Game.h"

game_space::Game::Game(int rows, int cols) : rows_{rows}, cols_{cols} {
  initscr();
  clear();
//  raw();
  cbreak();
  keypad(stdscr, true);
  noecho();
  curs_set(0);
  halfdelay(1);
  resize_term(rows, cols);

  game_state_ = ui::LOADING;
  loading_ = ui::Loading();
  main_menu_ = ui::MainMenu();
  game_config_.loadConfig();

}

void game_space::Game::start() {
  int key = ERR;
  game_state_ = loading_.update(key);

  while (game_state_ != ui::EXIT) {
    key = getch();
    switch (game_state_) {
      case ui::LOADING:game_state_ = loading_.update(key);
      if (game_state_ == ui::MAIN_MENU) {
        main_menu_.update(-1);
      }
        break;
      case ui::MAIN_MENU:game_state_ = main_menu_.update(key);
        break;
      case ui::SETTINGS:break;
      case ui::EXIT:finish();
        break;
      case ui::GAME_FIELD:break;
    }
  }
}

void game_space::Game::finish() {
  clear();
  endwin();
}

