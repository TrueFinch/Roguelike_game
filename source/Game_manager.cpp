//
// Created by truefinch on 17.05.18.
//


#include <ncurses.h>
#include "Game_manager.h"

game::Game_manager::Game_manager(int rows, int cols) : rows_{rows}, cols_{cols} {
  game_config_.loadConfig();
  ui_ = ui::UserInterface(*game_config_.getUIStat());

  initscr();
  clear();
//  raw();
  cbreak();
  keypad(stdscr, true);
  noecho();
  curs_set(0);
  halfdelay(1);
  resize_term(rows, cols);

//  loading_ = game_screen::Loading();
//  main_menu_ = game_screen::MainMenu();
  map_.loadMap(game_config_);

}

void game::Game_manager::start() {
  int key = ERR;
//  game_state_ = loading_.update(key);

  while (ui_.getGameState() != enums::EXIT) {
    key = getch();
    ui_.update(key);
  }
  finish();
}

void game::Game_manager::finish() {
  clear();
  endwin();
}

//std::shared_ptr<config::Config> game::Game_manager::getConfiguration() const {
//  return std::make_shared<config::Config>(game_config_);
//}

