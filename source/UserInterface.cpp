//
// Created by truefinch on 17.05.18.
//

#include <ncurses.h>
#include <cstring>
#include "../include/UserInterface.h"

int MainMenu::update(int key) { //default is -1
  clear();
  int max_height = 0, max_width = 0;
  getmaxyx(stdscr, max_height, max_width);
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
    default: break;
  }
  for (auto i = 0; i < menu_items_.size(); ++i) {
    if (i == chosen_) {
      mvaddch(max_height / 2 + i, ((max_width - menu_items_[i].size()) / 2), '>');
    } else {
      mvaddch(max_height / 2 + i, ((max_width - menu_items_[i].size()) / 2), ' ');
    }
    mvprintw(max_height / 2 + i, (int) ((max_width - menu_items_[i].size()) / 2) + 1, "%s\n", menu_items_[i].c_str());
  }
  return 0;
}

UserInterface::UserInterface(int rows, int cols) : rows_{rows}, cols_{cols} {
  initscr();
  clear();
  keypad(stdscr, true);
  noecho();
  curs_set(0);
  resize_term(rows, cols);
}

int UserInterface::update(int key) {
  main_menu_.update(key);
}
