//
// Created by truefinch on 17.05.18.
//


#include <ncurses.h>
#include "Game_manager.h"

game::Game_manager::Game_manager(int rows, int cols) : rows_{rows}, cols_{cols} {
  game_config_.loadConfig();
  ui_ = ui::UserInterface(*game_config_.getUIStat());
  hero_ptr_ = map_.loadMap(npc_, game_config_);
  game_state_ = enums::LOADING;
  std::shared_ptr<std::vector<std::string>> a = map_.getMapView();

  initscr();
  clear();
  cbreak();
  keypad(stdscr, true);
  noecho();
  curs_set(0);
  halfdelay(1);
  resize_term(rows, cols);
}

void game::Game_manager::start() {
  int key = ERR;
//  game_state_ = loading_.update(key);

  while (game_state_ != enums::EXIT) {
    key = getch();
    if (key != ERR) {
      switch (key) {
        case KEY_UP:
          break;
        case KEY_DOWN:
          break;
        case KEY_RIGHT:
          break;
        case KEY_LEFT:
          break;
        default:
          break;
      }
      if (game_state_ == enums::GAME_FIELD) {
        ui_.updateMap(map_.getMapView(), hero_ptr_->getCoord());
      }
    }
    game_state_ = ui_.update(game_state_, key);
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

