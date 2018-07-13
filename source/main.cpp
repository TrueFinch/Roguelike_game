#include <iostream>
#include <ncurses.h>
#include "GameManager.h"
#include <MapGenerator.h>

int main() {
  int max_rows, max_cols;
//  MapGenerator& gen = MapGenerator::Instance();
//  int rows = 10, cols = 20;
//  gen.setSize(rows, cols);
//  gen.initCanvas();
//  gen.readTiles();
//  gen.fillCanvas();
//  gen.addActors();
//  auto map = gen.getMap();
//  for (int i = 0; i < 5 * rows; ++i) {
//    for (int j = 0; j < 5 * cols; ++j) {
//      printf("%c", map[i][j]);
//    }
//    printf("\n");
//  }
//  gen.saveMap();
  game::GameManager& gameManager = game::GameManager::Instance();
  getmaxyx(stdscr, max_rows, max_cols);
  gameManager.init(max_rows, max_cols);
  gameManager.Start();

  return 0;
}