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
  int max_rows = 0, max_cols = 0;
  int map_rows, map_cols;
  map_rows = (int) map_.size(), map_cols = (int) map_.begin()->size();
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_ESC:
      new_state = enums::PAUSE_MENU;
      break;
    default:
      break;
  }

  mvaddch(max_rows / 2, max_cols / 2, map_[(int) hero_pos_.x][(int) hero_pos_.y]);
  int row = (int) hero_pos_.x, col = (int) hero_pos_.y,
      top_row_bound = row - std::min<int>(max_rows / 2, row),
      bottom_row_bound = row + std::min<int>(max_rows / 2, map_rows - row - 1),
      left_row_bound = col - std::min<int>(max_cols / 2, col),
      right_col_bound = col + std::min<int>(max_cols / 2, map_cols - col - 1);
  for (int i = top_row_bound; i <= bottom_row_bound; ++i) {
    for (int j = left_row_bound; j < right_col_bound; ++j) {
      mvaddch(max_rows / 2 - (int) hero_pos_.x + i, max_cols / 2 - (int) hero_pos_.y + j, map_[i][j]);
    }
  }

  this->status_bar_ = newwin(4, max_cols, 0, 0);
  GameField& game_field = GameField::Instance();
  game_field.displayHealth();
  game_field.displayMana();
  game_field.displayDamage();
  game_field.displayLevel();
  game_field.displayScore();
  game_field.displayInventory();
  return new_state;
}

void GameField::updateMap(const std::vector<std::string>& new_map,
                          const std::shared_ptr<actor::ActiveActor> hero_actor, int hp_potion_amount, int mp_potion_amount) {
  this->map_ = new_map;
  this->hero_pos_ = hero_actor->getPosition();
  this->max_health_points_ = hero_actor->getMaxHealthPoints();
  this->cur_health_points_ = hero_actor->getCurHealthPoints();
  this->max_mana_points_ = hero_actor->getMaxManaPoints();
  this->cur_mana_points_ = hero_actor->getCurManaPoints();
  this->damage_points_ = hero_actor->getDamagePoints();
  this->level_points_ = hero_actor->getLevelPoints();
  this->max_score_points_ = hero_actor->getMaxScorePoints();
  this->cur_score_points_ = hero_actor->getCurScorePoints();
  this->hp_potion_amount_ = hp_potion_amount;
  this->mp_potion_amount_ = mp_potion_amount;
}

void GameField::displayHealth() const {
  refresh();
  std::string status = "HP " + std::to_string(this->cur_health_points_) + "/" + std::to_string(this->max_health_points_);
  box(this->status_bar_, 0, 0);
  //TODO: move coords to config file
  mvwprintw(this->status_bar_, 1, 1, status.c_str());
  wrefresh(this->status_bar_);
}

void GameField::displayMana() const {
  refresh();
  std::string status = "MP " + std::to_string(this->cur_mana_points_) + "/" + std::to_string(this->max_mana_points_);
  box(this->status_bar_, 0, 0);
  //TODO: move coords to config file
  mvwprintw(this->status_bar_, 2, 1, status.c_str());
  wrefresh(this->status_bar_);
}

void GameField::displayDamage() const {
  refresh();
  std::string status = "Damage  " + std::to_string(this->damage_points_);
  box(this->status_bar_, 0, 0);
  //TODO: move coords to config file
  mvwprintw(this->status_bar_, 1, 20, status.c_str());
  wrefresh(this->status_bar_);
}

void GameField::displayLevel() const {
  refresh();
  std::string status = "Level  " + std::to_string(this->level_points_);
  box(this->status_bar_, 0, 0);
  //TODO: move coords to config file
  mvwprintw(this->status_bar_, 2, 20, status.c_str());
  wrefresh(this->status_bar_);
}

void GameField::displayScore() const {
  refresh();
  std::string status = "Score " + std::to_string(this->cur_score_points_) + "/" + std::to_string(this->max_score_points_);
  box(this->status_bar_, 0, 0);
  //TODO: move coords to config file
  mvwprintw(this->status_bar_, 2, 30, status.c_str());
  wrefresh(this->status_bar_);
}

void GameField::displayInventory() const {
  refresh();
  std::string status = "Inventory: ";
  box(this->status_bar_, 0, 0);
  //TODO: move coords to config file
  mvwprintw(this->status_bar_, 1, 50, status.c_str());
  status = "Health potion x";
  mvwprintw(this->status_bar_, 1, 62, status.c_str());
  mvwprintw(this->status_bar_, 1, 62 + status.length(), std::to_string(hp_potion_amount_).c_str());
  status = "Mana potion x";
  mvwprintw(this->status_bar_, 2, 62, status.c_str());
  mvwprintw(this->status_bar_, 2, 62 + status.length(), std::to_string(mp_potion_amount_).c_str());
  wrefresh(this->status_bar_);
}


