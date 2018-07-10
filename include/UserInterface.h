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
  static UserInterface& Instance();
//  void Init();
  enums::GameState update(enums::GameState game_state, int key);
  void updateMap(std::shared_ptr<std::vector<std::string>> map, Point hero_pos);
 private:
  UserInterface() = default;
  ~UserInterface() = default;

  UserInterface(UserInterface const&) = delete;
  UserInterface& operator= (UserInterface const&) = delete;
  game_screen::Loading loading_;
  game_screen::MainMenu main_menu_;
  game_screen::GameField game_field_;
  std::vector<std::vector<char>> map_view_;
};

} // namespace ui