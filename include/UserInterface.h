//
// Created by truefinch on 04.06.18.
//

#pragma once

#include <ncurses.h>
//#include <Screens.h>
#include <Config.h>
#include <Enums.h>
#include <nlohmann/json.hpp>
#include <MainMenu.h>
#include <Loading.h>
#include <GameField.h>

namespace ui {

class UserInterface {
 public:
  static UserInterface& Instance();
  void init();
  enums::GameState update(enums::GameState game_state, int key);
  void updateMap(const std::shared_ptr<std::vector<std::string>>& map,
                 const std::shared_ptr<actor::ActiveActor> hero_pos);
 private:
  UserInterface() = default;
  ~UserInterface() = default;

  UserInterface(UserInterface const&) = delete;
  UserInterface& operator=(UserInterface const&) = delete;
  std::vector<std::string> map_view_;
};

} // namespace ui