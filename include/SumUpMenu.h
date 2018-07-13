//
// Created by truefinch on 14.07.18.
//
#pragma once

#include <Enums.h>
#include <string>
#include <vector>
#include <ncurses.h>
#include <iostream>
#include <fstream>

class SumUpMenu {
 public:
  static SumUpMenu& Instance();
  enums::GameState update(const int& key);
  void updateStats(const int&, const int&, const int&, const int&, const int&, const int&, const std::vector<bool>&, bool);
  void init(const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&);

  int calculateScore() const;
  void saveUser(const int& score) const;

 private:
  SumUpMenu() = default;
  ~SumUpMenu() = default;

  SumUpMenu(SumUpMenu const&) = delete;
  SumUpMenu& operator=(SumUpMenu const&) = delete;

  std::string text_for_winner_;
  std::string text_for_loser_;
  std::string top_text_;
  std::string zombie_text_;
  std::string dragon_text_;
  std::string princess_text_;
  std::string level_text_;
  std::string achievement_text_;
  std::string step_text_;
  std::string score_text_;

  int zombie_killed_ = 0;
  int dragon_killed_ = 0;
  int princess_rescued_ = 0;
  int level_reached_ = 0;
  int score_got_ = 0;
  int steps_made_ = 0;

  std::vector<bool> achievements_;
  bool is_won_ = false;

  std::string nickname_;
};

