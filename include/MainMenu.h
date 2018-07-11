//
// Created by truefinch on 11.07.18.
//
#pragma once

//#include <UserInterface.h>
#include <Enums.h>
#include <ncurses.h>
#include <vector>
#include <string>

class MainMenu {
 public:
  static MainMenu& Instance();
  void setMenuItems(const std::vector<std::string>&);
  std::vector<std::string> getMenuItems() const;
  enums::GameState update(int key);
 private:
  MainMenu() = default;
  ~MainMenu() = default;

  MainMenu(MainMenu const&) = delete;
  MainMenu& operator= (MainMenu const&) = delete;

  int chosen_ = 0;
  std::vector<std::string> menu_items_;
};

