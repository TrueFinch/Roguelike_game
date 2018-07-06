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
  enums::GameState update(int key);
//  void updateMap()
  enums::GameState getGameState() const;
  void setGameState(enums::GameState);
 private:
  enums::GameState game_state_;
  game_screen::Loading loading_;
  game_screen::MainMenu main_menu_;
  game_screen::GameField game_field_;
  std::vector<std::vector<char>> map_view_;
};

} // namespace ui