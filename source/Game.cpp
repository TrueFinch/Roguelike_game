//
// Created by truefinch on 17.05.18.
//


#include <ncurses.h>
#include "../include/Game.h"

using namespace game_space;

Game::Game(int rows, int cols) : rows_{rows}, cols_{cols} {
  this->ui_ = UserInterface(rows, cols);
}

int Game::start() {
  int key = -1;
  ui_.update(key);

  while(true) {
    key = getch();
    if (key == KEY_ESC) {
      break;
    }
    ui_.update(key);
  }
}

