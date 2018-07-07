//
// Created by truefinch on 27.05.18.
//

#include "Statistics.h"
#include <utility>

stats::HPStat::HPStat(int max, int cur) : max_health_points_{max}, cur_health_points_{cur} {};

void stats::HPStat::setMaxHP(int hp) {
  this->max_health_points_ = hp;
}

int stats::HPStat::getMaxHP() const {
  return this->max_health_points_;
}

void stats::HPStat::setCurHP(int hp) {
  this->cur_health_points_ = hp;
}

int stats::HPStat::getCurHP() const {
  return this->cur_health_points_;
}

stats::MPStat::MPStat(int max, int cur) : max_mana_points_{max}, cur_mana_points_{cur} {};

void stats::MPStat::setMaxMP(int mp) {
  this->max_mana_points_ = mp;
}

int stats::MPStat::getMaxMP() const {
  return this->max_mana_points_;
}

void stats::MPStat::setCurMP(int mp) {
  this->cur_mana_points_ = mp;
}

int stats::MPStat::getCurMP() const {
  return this->cur_mana_points_;
}

stats::DPStat::DPStat(int max, int cur) : max_damage_points_{max}, cur_damage_points_{cur} {};

void stats::DPStat::setMaxDP(int dp) {
  this->max_damage_points_ = dp;
}

int stats::DPStat::getMaxDP() const {
  return this->max_damage_points_;
}

void stats::DPStat::setCurDP(int dp) {
  this->cur_damage_points_ = dp;
}

int stats::DPStat::getCurDP() const {
  return this->cur_damage_points_;
}

stats::VPStat::VPStat(int max, int cur) : max_visibility_points_{max}, cur_visibility_points_{cur} {};

void stats::VPStat::setMaxVP(int vp) {
  this->max_visibility_points_ = vp;
}

int stats::VPStat::getMaxVP() const {
  return this->max_visibility_points_;
}

void stats::VPStat::setCurVP(int vp) {
  this->cur_visibility_points_ = vp;
}

int stats::VPStat::getCurVP() const {
  return this->cur_visibility_points_;
}

stats::SpecialFlagsStat::SpecialFlagsStat(bool dead, bool immortal) : is_dead_{dead}, is_immortal_{immortal} {};

void stats::SpecialFlagsStat::setDead(bool flag) {
  this->is_dead_ = flag;
}

bool stats::SpecialFlagsStat::isDead() const {
  return this->is_dead_;
}

void stats::SpecialFlagsStat::setImmortal(bool flag) {
  this->is_immortal_ = flag;
}

bool stats::SpecialFlagsStat::isImmortal() const {
  return this->is_immortal_;
}

stats::SymbolsStat::SymbolsStat(char dead, char undead) : dead_symbol_{dead}, undead_symbol_{undead} {}

void stats::SymbolsStat::setDeadSymbol(char c) {
  this->dead_symbol_ = c;
}

char stats::SymbolsStat::getDeadSymbol() const {
  return this->dead_symbol_;
}

void stats::SymbolsStat::setUndeadSymbol(char c) {
  this->undead_symbol_ = c;
}

char stats::SymbolsStat::getUndeadSymbol() const {
  return this->undead_symbol_;
}

stats::CoordinateStat::CoordinateStat(Point p) : coordinate_{p} {}

stats::CoordinateStat::CoordinateStat(double row, double col) : coordinate_{row, col} {};

void stats::CoordinateStat::setCoord(Point p) {
  this->coordinate_ = p;
}

Point stats::CoordinateStat::getCoord() const {
  return this->coordinate_;
}

stats::HeroStat::HeroStat(int max_hp,
                          int cur_hp,
                          int max_mp,
                          int cur_mp,
                          int max_dp,
                          int cur_dp,
                          int max_vp,
                          int cur_vp,
                          char dead_symbol,
                          char undead_symbol,
                          bool is_dead,
                          bool is_immortal,
                          Point p) : HPStat(max_hp, cur_hp),
                                     MPStat(max_mp, cur_mp),
                                     DPStat(max_dp, cur_dp),
                                     VPStat(max_vp, cur_vp),
                                     SymbolsStat(dead_symbol, undead_symbol),
                                     SpecialFlagsStat(is_dead, is_immortal),
                                     CoordinateStat(p) {}

stats::PrincessStat::PrincessStat(int max_mp,
                                  int cur_mp,
                                  int max_vp,
                                  int cur_vp,
                                  char dead_symbol,
                                  char undead_symbol,
                                  bool is_dead,
                                  bool is_immortal,
                                  Point p) : MPStat(max_mp, cur_mp),
                                             VPStat(max_vp, cur_vp),
                                             SymbolsStat(dead_symbol, undead_symbol),
                                             SpecialFlagsStat(is_dead, is_immortal),
                                             CoordinateStat(p) {}

stats::ZombieStat::ZombieStat(int max_hp,
                              int cur_hp,
                              int max_dp,
                              int cur_dp,
                              int max_vp,
                              int cur_vp,
                              char dead_symbol,
                              char undead_symbol,
                              bool is_dead,
                              bool is_immortal,
                              Point p) : HPStat(max_hp, cur_hp),
                                         DPStat(max_dp, cur_dp),
                                         VPStat(max_vp, cur_vp),
                                         SymbolsStat(dead_symbol, undead_symbol),
                                         SpecialFlagsStat(is_dead, is_immortal),
                                         CoordinateStat(p) {}

stats::DragonStat::DragonStat(int max_hp,
                              int cur_hp,
                              int max_mp,
                              int cur_mp,
                              int max_dp,
                              int cur_dp,
                              int max_vp,
                              int cur_vp,
                              char dead_symbol,
                              char undead_symbol,
                              bool is_dead,
                              bool is_immortal,
                              Point p) : HPStat(max_hp, cur_hp),
                                         MPStat(max_mp, cur_mp),
                                         DPStat(max_dp, cur_dp),
                                         VPStat(max_vp, cur_vp),
                                         SymbolsStat(dead_symbol, undead_symbol),
                                         SpecialFlagsStat(is_dead, is_immortal),
                                         CoordinateStat(p) {}

stats::WallStat::WallStat(int max_hp,
                          int cur_hp,
                          char dead_symbol,
                          char undead_symbol,
                          bool is_dead,
                          bool is_immortal,
                          Point p) : HPStat(max_hp, cur_hp),
                                     SymbolsStat(dead_symbol, undead_symbol),
                                     SpecialFlagsStat(is_dead, is_immortal),
                                     CoordinateStat(p) {}

stats::LoadingStat::LoadingStat(std::string greeting, std::string hint) {
  greeting_ = std::move(greeting);
  hint_ = std::move(hint);
}

void stats::LoadingStat::setGreeting(std::string greeting) {
  greeting_ = std::move(greeting);
}

std::string stats::LoadingStat::getGreeting() {
  return greeting_;
}

void stats::LoadingStat::setHint(std::string hint) {
  hint_ = std::move(hint);
}

std::string stats::LoadingStat::getHint() {
  return hint_;
}

stats::MainMenuStat::MainMenuStat(std::vector<std::string> menu_items) {
  for (const auto& i : menu_items) {
    menu_items_.push_back(i);
  }
}

void stats::MainMenuStat::setMenuItems(std::vector<std::string> menu_items) {
  for (const auto& i : menu_items) {
    menu_items_.push_back(i);
  }
}

std::vector<std::string> stats::MainMenuStat::getMenuItems() {
  return menu_items_;
}

stats::UIStat::UIStat(std::string& greeting,
                      std::string& hint,
                      std::vector<std::string>& main_menu) : LoadingStat(greeting, hint),
                                                            MainMenuStat(main_menu) {}
