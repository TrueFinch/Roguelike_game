//
// Created by truefinch on 17.05.18.
//

#include <ncurses.h>
#include <cstring>
#include <cassert>
#include "../include/UserInterface.h"

ui::GameState ui::Loading::update(int key) {
  clear();
  ui::GameState new_state = ui::LOADING;
  int max_rows = 0, max_cols = 0;
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_ESC:
      new_state = ui::EXIT;
      break;
    case -1:
      mvwprintw(stdscr, max_rows / 2, (max_cols - (int) greeting_msg_.length()) / 2, "%s", greeting_msg_);
      mvwprintw(stdscr, max_rows - 1, 0, "Press any key to continue or ESCAPE to exit");
      break;
    default:
      new_state = ui::MAIN_MENU;
      break;
  }
  return new_state;
}

ui::GameState ui::MainMenu::update(int key) {
  clear();
  ui::GameState new_state = MAIN_MENU;
  int max_rows = 0, max_cols = 0;
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_UP:
      if (chosen_ > 0) {
        --chosen_;
      }
      break;
    case KEY_DOWN:
      if (chosen_ < menu_items_.size() - 1)
        ++chosen_;
      break;
    case KEY_ESC:new_state = ui::EXIT;
      break;
    case KEY_ENT:
      switch (chosen_) {
        case 0:new_state = ui::GAME_FIELD;
          break;
        case 1:new_state = ui::SETTINGS;
          break;
        case 2:new_state = ui::EXIT;
          break;
        default:assert(false);
          break;
      }
      break;
    default: break;
  }
  for (auto i = 0; i < menu_items_.size(); ++i) {
    if (i == chosen_) {
      mvaddch(max_rows / 2 + i, ((max_cols - menu_items_[i].size()) / 2), '>');
    } else {
      mvaddch(max_rows / 2 + i, ((max_cols - menu_items_[i].size()) / 2), ' ');
    }
    mvprintw(max_rows / 2 + i, (int) ((max_cols - menu_items_[i].size()) / 2) + 1, "%s\n", menu_items_[i].c_str());
  }
  return new_state;
}