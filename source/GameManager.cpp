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
//  game_config_.loadConfig();
  //TODO: Add initialization of UI
  //TODO: Add loading of map and configuration
//  ui_ = ui::UserInterface(*game_config_.getUIStat());
//  hero_ptr_ = map::Map::Instance().loadMap(actors_, game_config_);
  game_state_ = enums::LOADING;
  std::shared_ptr<std::vector<std::string>> a = map::Map::Instance().getMapView();

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
        for (const auto& actor : actors_) {

        }
//        ui_.updateMap(map_.getMapView(), hero_ptr_->getCoord());
      }
    }
//    game_state_ = ui_.update(game_state_, key);
  }
  Finish();
}

void game::GameManager::Finish() {
  clear();
  endwin();
}

std::vector<std::vector<std::shared_ptr<map::Cell>>> game::GameManager::getArea() const {
  return std::vector<std::vector<std::shared_ptr<map::Cell>>>();
}

void game::GameManager::setLastPressedKey(int) {

}

int game::GameManager::getLastPressedKey() const {
  return 0;
}

void game::GameManager::swap(Point a, Point b) const {

}
//std::shared_ptr<config::Config> game::GameManager::getConfiguration() const {
//  return std::make_shared<config::Config>(game_config_);
//}

