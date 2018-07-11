//
// Created by truefinch on 17.05.18.
//
#pragma once

#include <string>
#include <vector>
#include <Enums.h>
#include <Statistics.h>
#include <memory>

namespace game_screen {

class Screen {
 public:
  Screen() = default;
  virtual enums::GameState update(int key) = 0;
  ~Screen() = default;
};

class GameField : public Screen {
 public:
  GameField() = default;
  enums::GameState update(int key) override;
  enums::GameState updateMap(std::shared_ptr<std::vector<std::string>>, Point hero_pos);
  std::vector<std::string> getMenuItems();
 private:
  Point hero_pos_ = {0, 0};
  std::vector<std::string> map_;
  int damage_points_ = 0;
  int cur_mana_points_ = 0;
  int max_mana_points_ = 0;
  int cur_health_points_ = 0;
  int max_health_points_ = 0;
};

} // namespace game_screen
