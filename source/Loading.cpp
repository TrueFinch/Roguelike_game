//
// Created by truefinch on 11.07.18.
//

#include "Loading.h"

Loading& Loading::Instance() {
  static Loading self;
  return self;
}

enums::GameState Loading::update(const int key) {
  clear();
  enums::GameState new_state = enums::LOADING;
  int max_rows = 0, max_cols = 0;
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_ENT:
      new_state = enums::MAIN_MENU;
      break;
    case KEY_ESC:
      new_state = enums::EXIT;
      break;
    default:
      break;
  }
  mvwprintw(stdscr, max_rows / 2, (max_cols - (int) getGreeting().length()) / 2, "%s", getGreeting().c_str());
  mvwprintw(stdscr, max_rows - 1, 0, getHint().c_str());
  refresh();
  return new_state;
}

void Loading::setGreeting(const std::string& s) {
  greeting_ = s;
}

std::string Loading::getGreeting() {
  return greeting_;
}

void Loading::setHint(const std::string& s) {
  hint_ = s;
}

std::string Loading::getHint() {
  return hint_;
}
