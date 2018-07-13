//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Enums.h>
#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>
#include <Point.h>
#include "Actors.h"

class GameField {
 public:
  static GameField& Instance();
  enums::GameState update(int key);
  void updateMap(const std::vector<std::string>&, std::shared_ptr<actor::ActiveActor> hero_actor, int hp_potion_amount,
                 int mp_potion_amount);
 private:
  GameField() = default;
  ~GameField() = default;

  GameField(GameField const&) = delete;
  GameField& operator=(GameField const&) = delete;

  void displayHealth() const;
  void displayMana() const;
  void displayDamage() const;
  void displayLevel() const;
  void displayScore() const;
  void displayInventory() const;

  WINDOW* status_bar_;
  Point hero_pos_ = {0, 0};
  std::vector<std::string> map_;
  int max_health_points_ = 0;
  int cur_health_points_ = 0;
  int max_mana_points_ = 0;
  int cur_mana_points_ = 0;
  int damage_points_ = 0;
  int level_points_ = 0;
  int max_score_points_ = 0;
  int cur_score_points_ = 0;
  int hp_potion_amount_ = 0;
  int mp_potion_amount_ = 0;
};

