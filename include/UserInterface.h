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

enum GameState { LOADING = 0, MAIN_MENU, GAME_FIELD, SETTINGS, EXIT};

class Screen {
 public:
  Screen() = default;
  virtual GameState update(int key) = 0;
  ~Screen() = default;
};

class Loading: Screen {
 public:
  Loading() = default;
  GameState update(int key) override;
 private:
  std::string greeting_msg_ = "WELCOME TO MY ROGUELIKE GAME";
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