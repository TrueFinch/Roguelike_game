//
// Created by truefinch on 11.07.18.
//

#include <cassert>
#include "MainMenu.h"

MainMenu& MainMenu::Instance() {
  static MainMenu self;
  return self;
};

void MainMenu::setMenuItems(const std::vector<std::string>& menu_items) {
  menu_items_.clear();
  for (const auto& i : menu_items) {
    menu_items_.push_back(i);
  }
}

std::vector<std::string> MainMenu::getMenuItems() const {
  return menu_items_;
}

enums::GameState MainMenu::update(const int key) {
  clear();
  enums::GameState new_state = enums::MAIN_MENU;
  int max_rows = 0, max_cols = 0;
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_UP:
      if (chosen_ > 0) {
        --chosen_;
      }
      break;
    case KEY_DOWN:
      if (chosen_ < (int) getMenuItems().size() - 1)
        ++chosen_;
      break;
    case KEY_ESC:
      new_state = enums::EXIT;
      break;
    case KEY_ENT:
      switch (chosen_) {
        case 0:
          new_state = enums::GAME_FIELD;
          break;
        case 1:
          new_state = enums::SETTINGS;
          break;
        case 2:
          new_state = enums::EXIT;
          break;
        default:
          assert(false);
          break;
      }
      break;
    default:
      break;
  }
  for (auto i = 0; i < (int) getMenuItems().size(); ++i) {
    if (i == chosen_) {
      mvaddch(max_rows / 2 + i, ((max_cols - getMenuItems()[i].size()) / 2), '>');
    } else {
      mvaddch(max_rows / 2 + i, ((max_cols - getMenuItems()[i].size()) / 2), ' ');
    }
    mvprintw(max_rows /2 + i, ((max_cols - getMenuItems()[i].size()) / 2) + 1, "%s\n", getMenuItems()[i].c_str());
  }
  refresh();
  return new_state;
}
