//
// Created by truefinch on 17.05.18.
//

#ifndef ROGUELIKE_GAME_H
#define ROGUELIKE_GAME_H

#include "UserInterface.h"

namespace game_space {

class Game {
 public:
  Game() = default;
  Game(int rows, int cols);
  void start();
  void finish();
 private:
  ui::GameState game_state = ui::MAIN_MENU;
  ui::MainMenu main_menu_ = ui::MainMenu();
  int rows_ = 0, cols_ = 0;
};

} //namespace game_space

#endif //ROGUELIKE_GAME_H
