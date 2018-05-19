//
// Created by truefinch on 17.05.18.
//

#ifndef ROGUELIKE_USERINTERFACE_H
#define ROGUELIKE_USERINTERFACE_H

#include <string>
#include <vector>

namespace ui {

#define KEY_ENT 10
#define KEY_ESC 27

enum GameState { MAIN_MENU = 1, EXIT};

class Screen {
 public:
  Screen() = default;
  virtual GameState update(int key) = 0;
  ~Screen() = default;
};

class MainMenu : Screen {
 public:
  MainMenu() = default;
  GameState update(int key) override;
 private:
  std::vector<std::string> menu_items_{"NEW GAME", "SETTINGS", "EXIT"};
  int chosen_ = 0;
};

} // namespace ui

#endif //ROGUELIKE_USERINTERFACE_H