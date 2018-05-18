//
// Created by truefinch on 17.05.18.
//

#ifndef ROGUELIKE_USERINTERFACE_H
#define ROGUELIKE_USERINTERFACE_H

#include <string>
#include <vector>

#define KEY_ESC 27

class Screen {
 public:
  Screen() = default;
  virtual int update(int key) = 0;
  ~Screen() = default;
};

class MainMenu : Screen {
 public:
  int update(int key) override;
 private:
  std::vector<std::string> menu_items_{"NEW GAME", "SETTINGS", "EXIT"};
  int chosen_ = 0;
};

class UserInterface {
 public:
  UserInterface() = default;
  UserInterface(int rows, int cols);
  int update(int key);
 private:
  int rows_ = 0, cols_ = 0;
  MainMenu main_menu_;
};

#endif //ROGUELIKE_USERINTERFACE_H
