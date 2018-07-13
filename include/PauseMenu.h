//
// Created by truefinch on 14.07.18.
//
#pragma once

#include <Enums.h>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cassert>

class PauseMenu {
 public:
  static PauseMenu& Instance();
  enums::GameState update(const int& key);
  void init(const std::vector<std::string>&);
 private:
  PauseMenu() = default;
  ~PauseMenu() = default;

  PauseMenu(PauseMenu const&) = delete;
  PauseMenu& operator= (PauseMenu const&) = delete;

  int chosen_ = 0;
  std::vector<std::string> menu_items_;
};

