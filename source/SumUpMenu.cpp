//
// Created by truefinch on 14.07.18.
//

#include "SumUpMenu.h"

enums::GameState SumUpMenu::update(const int& key) {
  clear();
  enums::GameState new_state = enums::SUM_UP_MENU;
  int max_rows, max_cols;
  getmaxyx(stdscr, max_rows, max_cols);
  if (((key >= 48) and (key <= 57)) or ((key >= 65) and (key <= 90)) or ((key >= 97) and (key <= 122))) {
    nickname_.push_back(char(key));
  } else if (key == KEY_ENT) {
    saveUser(calculateScore());
    new_state = enums::MAIN_MENU;
  }
  if (is_won_) {
    mvprintw(3, max_cols / 2 - text_for_winner_.size() / 2, "%s", text_for_winner_.c_str());
  } else {
    mvprintw(3, max_cols / 2 - text_for_loser_.size() / 2, "%s", text_for_loser_.c_str());
  }
  mvprintw(5, max_cols / 2 - top_text_.size(), "%s", top_text_.c_str());
  mvprintw(5, max_cols / 2, "%s", nickname_.c_str());

  mvprintw(7, max_cols / 2 - zombie_text_.size(), "%s", zombie_text_.c_str());
  mvprintw(7, max_cols / 2, "%s", std::to_string(zombie_killed_).c_str());

  mvprintw(8, max_cols / 2 - dragon_text_.size(), "%s", dragon_text_.c_str());
  mvprintw(8, max_cols / 2, "%s", std::to_string(dragon_killed_).c_str());

  mvprintw(9, max_cols / 2 - princess_text_.size(), "%s", princess_text_.c_str());
  mvprintw(9, max_cols / 2, "%s", std::to_string(princess_rescued_).c_str());

  mvprintw(10, max_cols / 2 - level_text_.size(), "%s", level_text_.c_str());
  mvprintw(10, max_cols / 2, "%s", std::to_string(level_reached_).c_str());

  mvprintw(11, max_cols / 2 - step_text_.size(), "%s", step_text_.c_str());
  mvprintw(11, max_cols / 2, "%s", std::to_string(steps_made_).c_str());

  mvprintw(12, max_cols / 2 - score_text_.size(), "%s", score_text_.c_str());
  mvprintw(12, max_cols / 2, "%s", std::to_string(score_got_).c_str());

  refresh();
  return new_state;
}

int SumUpMenu::calculateScore() const {
  return score_got_ + princess_rescued_ * 100 + steps_made_ / 50;
}

void SumUpMenu::init(const std::string& winning_text,
                     const std::string& losing_text,
                     const std::string& top_text,
                     const std::string& zombie,
                     const std::string& dragon,
                     const std::string& princess,
                     const std::string& level,
                     const std::string& steps,
                     const std::string& achievement,
                     const std::string& score) {
  text_for_winner_ = winning_text;
  text_for_loser_ = losing_text;
  top_text_ = top_text;
  zombie_text_ = zombie;
  dragon_text_ = dragon;
  princess_text_ = princess;
  level_text_ = level;
  step_text_ = steps;
  score_text_ = score;
  achievement_text_ = achievement;
}

void SumUpMenu::updateStats(const int& zombie_killed,
                            const int& dragon_killed,
                            const int& princess_rescued,
                            const int& level_reached,
                            const int& score_got,
                            const int& steps_made,
                            const std::vector<bool>& achievements,
                            bool is_won) {
  zombie_killed_ = zombie_killed;
  dragon_killed_ = dragon_killed;
  princess_rescued_ = princess_rescued;
  level_reached_ = level_reached;
  score_got_ = score_got;
  steps_made_ = steps_made;
  achievements_ = achievements;
  is_won_ = is_won;
}

SumUpMenu& SumUpMenu::Instance() {
  static SumUpMenu self;
  return self;
}

void SumUpMenu::saveUser(const int& score) const {
  std::ofstream fout;
  fout.open("/home/truefinch/CLionProjects/Roguelike_game/records/record_holders", std::ios_base::app);
  fout << nickname_ << std::endl << score << std::endl;
  for (int i = 0; i < achievements_.size(); ++i) {
    fout << achievements_[i] << ' ';
  }
  fout << std::endl << '#' << std::endl;
  fout.close();
}


