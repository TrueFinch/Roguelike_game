//
// Created by truefinch on 17.05.18.
//


#include <ncurses.h>
#include "GameManager.h"

game::GameManager& game::GameManager::Instance() {
  static GameManager self;
  return self;
}

void game::GameManager::Init(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  game_config_.loadConfig();
  ui_ = ui::UserInterface(*game_config_.getUIStat());
  hero_ptr_ = map_.loadMap(actors_, game_config_);
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

void game::GameManager::Start() {
  int key = ERR;
//  game_state_ = loading_.update(key);

  while (game_state_ != enums::EXIT) {
    key = getch();
    if (key != ERR) {
      if (game_state_ == enums::GAME_FIELD) {
        Point direction;
        switch (key) {
          case KEY_UP:
            direction = {-1, 0};
            break;
          case KEY_DOWN:
            direction = {1, 0};
            break;
          case KEY_RIGHT:
            direction = {0, 1};
            break;
          case KEY_LEFT:
            direction = {0, -1};
            break;
          default:
            break;
        }
        for (const auto& actor : actors_) {

        }
//        ui_.updateMap(map_.getMapView(), hero_ptr_->getCoord());
      }
    }
    game_state_ = ui_.update(game_state_, key);
  }
  Finish();
}

void game::GameManager::Finish() {
  clear();
  endwin();
}
//std::shared_ptr<config::Config> game::GameManager::getConfiguration() const {
//  return std::make_shared<config::Config>(game_config_);
//}

