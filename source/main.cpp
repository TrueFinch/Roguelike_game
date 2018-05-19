#include <iostream>
#include <ncurses.h>
#include "Game.h"

int main() {
  game_space::Game game(45, 125);
  game.start();
  return 0;
}