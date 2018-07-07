//
// Created by truefinch on 04.06.18.
//

#pragma once

#include <ncurses.h>
#include <Screens.h>
#include <Enums.h>
#include <Config.h>
#include <Statistics.h>

namespace ui {

class UserInterface{
 public:
  UserInterface() = default;
  explicit UserInterface(stats::UIStat stat);
  enums::GameState update(enums::GameState game_state, int key);
  void updateMap(std::shared_ptr<std::vector<std::string>> map, Point hero_pos);
 private:
  game_screen::Loading loading_;
  game_screen::MainMenu main_menu_;
  game_screen::GameField game_field_;
  std::vector<std::vector<char>> map_view_;
};

} // namespace ui