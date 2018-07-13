//
// Created by truefinch on 14.07.18.
//

#include "PauseMenu.h"

PauseMenu& PauseMenu::Instance() {
  static PauseMenu self;
  return self;
}

enums::GameState PauseMenu::update(const int& key) {
  enums::GameState new_state = enums::PAUSE_MENU;
  int max_rows, max_cols;
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_UP:
      if (chosen_ > 0) {
        --chosen_;
      }
      break;
    case KEY_DOWN:
      if (chosen_ < (int) menu_items_.size() - 1)
        ++chosen_;
      break;
    case KEY_ESC:
      new_state = enums::GAME_FIELD;
      break;
    case KEY_ENT:
      switch (chosen_) {
        case 0:
          new_state = enums::GAME_FIELD;
          break;
        case 1:
          new_state = enums::SUM_UP_MENU;
          break;
        default:
          assert(false);
          break;
      }
      break;
    default:
      break;
  }

  WINDOW* win = newwin(4, max_cols / 2, max_rows / 2 - 2, max_cols / 4);

  for (auto i = 0; i < (int) menu_items_.size(); ++i) {
    if (i == chosen_) {
      mvwaddch(win, i + 1, 1, '>');
    } else {
      mvwaddch(win, i + 1, 1, ' ');
    }
    mvwprintw(win, i + 1, 2, "%s\n", menu_items_[i].c_str());
  }

  refresh();
  box(win, 0, 0);
  wrefresh(win);
  return new_state;
}

void PauseMenu::init(const std::vector<std::string>& menu_items) {
  PauseMenu& menu = PauseMenu::Instance();
  menu.menu_items_.clear();
  for (const auto& i : menu_items) {
    menu.menu_items_.push_back(i);
  }
}

