//
// Created by truefinch on 17.05.18.
//

#include <ncurses.h>
#include <cstring>
#include <cassert>
#include "Screens.h"
#include <algorithm>

#define KEY_ENT 10
#define KEY_ESC 27

//enums::GameState game_screen::Loading::update(int key) {
//  clear();
//  enums::GameState new_state = enums::LOADING;
//  int max_rows = 0, max_cols = 0;
//  getmaxyx(stdscr, max_rows, max_cols);
//  switch (key) {
//    case KEY_ENT:
//      new_state = enums::MAIN_MENU;
//      break;
//    case KEY_ESC:
//      new_state = enums::EXIT;
//      break;
//    default:
//      break;
//  }
//  mvwprintw(stdscr, max_rows / 2, (max_cols - (int) getGreeting().length()) / 2, "%s", getGreeting().c_str());
//  mvwprintw(stdscr, max_rows - 1, 0, getHint().c_str());
//  refresh();
//  return new_state;
//}

//enums::GameState game_screen::MainMenu::update(int key) {
//  clear();
//  enums::GameState new_state = enums::MAIN_MENU;
//  int max_rows = 0, max_cols = 0;
//  getmaxyx(stdscr, max_rows, max_cols);
//  switch (key) {
//    case KEY_UP:
//      if (chosen_ > 0) {
//        --chosen_;
//      }
//      break;
//    case KEY_DOWN:
//      if (chosen_ < (int) getMenuItems().size() - 1)
//        ++chosen_;
//      break;
//    case KEY_ESC:
//      new_state = enums::EXIT;
//      break;
//    case KEY_ENT:
//      switch (chosen_) {
//        case 0:
//          new_state = enums::GAME_FIELD;
//          break;
//        case 1:
//          new_state = enums::SETTINGS;
//          break;
//        case 2:
//          new_state = enums::EXIT;
//          break;
//        default:
//          assert(false);
//          break;
//      }
//      break;
//    default:
//      break;
//  }
//  for (auto i = 0; i < (int) getMenuItems().size(); ++i) {
//    if (i == chosen_) {
//      mvaddch(max_rows / 2 + i, ((max_cols - getMenuItems()[i].size()) / 2), '>');
//    } else {
//      mvaddch(max_rows / 2 + i, ((max_cols - getMenuItems()[i].size()) / 2), ' ');
//    }
//    mvprintw(max_rows /2 + i, ((max_cols - getMenuItems()[i].size()) / 2) + 1, "%s\n", getMenuItems()[i].c_str());
//  }
//  refresh();
//  return new_state;
//}

enums::GameState game_screen::GameField::update(int key) {
  clear();
  enums::GameState new_state = enums::GAME_FIELD;
  int max_rows = 0, max_cols = 0, map_rows = (int) map_.size(), map_cols = (int) map_.begin()->size();
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_ESC:
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

enums::GameState game_screen::GameField::updateMap(const std::shared_ptr<std::vector<std::string>> new_map, Point hero_pos) {
  this->hero_pos_ = hero_pos;
  this->map_ = *new_map;
}