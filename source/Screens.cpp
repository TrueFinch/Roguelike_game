//
// Created by truefinch on 17.05.18.
//

#include <ncurses.h>
#include <cstring>
#include <cassert>
#include "Screens.h"

#define KEY_ENT 10
#define KEY_ESC 27

enums::GameState game_screen::Loading::update(int key) {
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
      mvwprintw(stdscr, max_rows / 2, (max_cols - (int) getGreeting().length()) / 2, "%s", getGreeting().c_str());
      mvwprintw(stdscr, max_rows - 1, 0, getHint().c_str());
      break;
  }
  refresh();
  return new_state;
}

enums::GameState game_screen::MainMenu::update(int key) {
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
    mvprintw(max_rows / 2 + i, (int) ((max_cols - getMenuItems()[i].size()) / 2) + 1, "%s\n", getMenuItems()[i].c_str());
  }
  refresh();
  return new_state;
}

enums::GameState game_screen::GameField::update(int key) {
  clear();
  enums::GameState new_state = enums::GAME_FIELD;
  int max_rows = 0, max_cols = 0;
  getmaxyx(stdscr, max_rows, max_cols);
  switch (key) {
    case KEY_ESC:
      new_state = enums::MAIN_MENU;
  }

  return new_state;
}