//
// Created by truefinch on 17.05.18.
//

#ifndef ROGUELIKE_GAME_H
#define ROGUELIKE_GAME_H

#include "UserInterface.h"
#include <Actors.h>
#include <Map.h>
#include <Config.h>

namespace game_space {

class Game {
 public:
  Game() = default;
  Game(int rows, int cols);
  void start();
  void finish();
 private:
  ui::GameState game_state_;
  ui::Loading loading_;
  ui::MainMenu main_menu_;
  map::Map map_;
  config::Config game_config_;
  int rows_ = 0, cols_ = 0;
};

} //namespace game_space

#endif //ROGUELIKE_GAME_H
