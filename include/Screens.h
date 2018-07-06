//
// Created by truefinch on 17.05.18.
//
#pragma once

#include <string>
#include <vector>
#include <Enums.h>
#include <Statistics.h>

namespace game_screen {

class Screen {
 public:
  Screen() = default;
  virtual enums::GameState update(int key) = 0;
  ~Screen() = default;
};

class Loading : public Screen, public stats::LoadingStat {
 public:
  Loading() = default;
  enums::GameState update(int key) override;
};

class MainMenu : public Screen, public stats::MainMenuStat{
 public:
  MainMenu() = default;
  enums::GameState update(int key) override;
 private:
  int chosen_ = 0;
};

class GameField : public Screen {
 public:
  GameField() = default;
  enums::GameState update(int key) override;
 private:
  std::vector<std::string> map_;
  int damage_points_ = 0;
  int cur_mana_points_ = 0;
  int max_mana_points_ = 0;
  int cur_health_points_ = 0;
  int max_health_points_ = 0;
};

} // namespace game_screen
