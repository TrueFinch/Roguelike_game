//
// Created by truefinch on 11.07.18.
//

#include "GameField.h"

GameField& GameField::Instance() {
  static GameField self;
  return self;
}

enums::GameState GameField::update(int key) {
  clear();
  enums::GameState new_state = enums::GAME_FIELD;
  int max_rows = 0, max_cols = 0, map_rows = (int) map_.size(), map_cols = (int) map_.begin()->size();
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_ESC:
      //TODO: add some medium menu
      new_state = enums::MAIN_MENU;
      break;
    default:
      break;
  }
//  for (int i = 0; i < map_rows; ++i) {
//    mvprintw(max_rows / 2 - map_rows / 2, max_cols / 2 - map_cols / 2, map_[i].c_str());
//  }
  mvaddch(max_rows / 2, max_cols / 2, map_[(int) hero_pos_.x][(int) hero_pos_.y]);
  for (int i = 0; i < std::min(map_rows, max_rows); ++i) {
    for (int j = 0; j < std::min(map_cols, max_cols); ++j) {
      mvaddch(max_rows / 2 - (int) hero_pos_.x + i, max_cols / 2 - (int) hero_pos_.y + j, map_[i][j]);
    }
  }
//  mvprintw((int)hero_pos_.x, (int)hero_pos_.y, map[hero_pos_.x][hero_pos_.y]);
//  for (int i = 0;)
  return new_state;
}

void GameField::updateMap(const std::vector<std::string>& new_map, const std::shared_ptr<actor::ActiveActor> hero_actor) {
  this->map_ = new_map;
  this->hero_pos_ = hero_actor->getPosition();
  this->max_health_points_ = hero_actor->getMaxHealthPoints();
  this->cur_health_points_ = hero_actor->getCurHealthPoints();
  this->max_mana_points_ = hero_actor->getMaxManaPoints();
  this->cur_mana_points_ = hero_actor->getCurManaPoints();
  this->damage_points_ = hero_actor->getDamagePoints();
  this->level_points = hero_actor->getLevelPoints();
  this->max_score_points = hero_actor->getMaxScorePoints();
  this->cur_score_points = hero_actor->getCurScorePoints();
}


