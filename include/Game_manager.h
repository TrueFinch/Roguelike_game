//
// Created by truefinch on 17.05.18.
//
#pragma once

#include <UserInterface.h>
#include <Actors.h>
#include <Map.h>
#include <Config.h>

namespace game {

class Game_manager {
 public:
  Game_manager(int rows, int cols);
  void start();
  void finish();
//  void loadMap
//  std::shared_ptr<config::Config> getConfiguration() const;
 private:
//  enums::GameState game_state_;
  ui::UserInterface ui_;
  config::Config game_config_;
  map::Map map_;

  int rows_ = 0, cols_ = 0;
};

} //namespace game
