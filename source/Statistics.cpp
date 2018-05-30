//
// Created by truefinch on 27.05.18.
//

#include "Statistics.h"

stats::HPStat::HPStat(int max, int cur) : max_health_points_{max}, cur_health_points_{cur} {};

void stats::HPStat::setMaxHP(int hp) {
  max_health_points_ = hp;
}

int stats::HPStat::getMaxHP() const {
  return max_health_points_;
}

void stats::HPStat::setCurHP(int hp) {
  cur_health_points_ = hp;
}

int stats::HPStat::getCurHP() const {
  return cur_health_points_;
}

stats::MPStat::MPStat(int max, int cur) : max_mana_points_{max}, cur_mana_points_{cur} {};

void stats::MPStat::setMaxMP(int mp) {
  max_mana_points_ = mp;
}

int stats::MPStat::getMaxMP() const {
  return max_mana_points_;
}

void stats::MPStat::setCurMP(int mp) {
  cur_mana_points_ = mp;
}

int stats::MPStat::getCurMP() const {
  return cur_mana_points_;
}

stats::DPStat::DPStat(int max, int cur) : max_damage_points_{max}, cur_damage_points_{cur} {};

void stats::DPStat::setMaxDP(int dp) {
  max_damage_points_ = dp;
}

int stats::DPStat::getMaxDP() const {
  return max_damage_points_;
}

void stats::DPStat::setCurDP(int dp) {
  cur_damage_points_ = dp;
}

int stats::DPStat::getCurDP() const {
  return cur_damage_points_;
}

stats::VPStat::VPStat(int max, int cur) : max_visibility_points_{max}, cur_visibility_points_{cur} {};

void stats::VPStat::setMaxVP(int vp) {
  max_visibility_points_ = vp;
}

int stats::VPStat::getMaxVP() const {
  return max_visibility_points_;
}

void stats::VPStat::setCurVP(int vp) {
  cur_visibility_points_ = vp;
}

int stats::VPStat::getCurVP() const {
  return cur_visibility_points_;
}

stats::SpecialFlagsStat::SpecialFlagsStat(bool dead, bool immortal) : is_dead_{dead}, is_immortal_{immortal} {};

void stats::SpecialFlagsStat::setDead(bool flag) {
  is_dead_ = flag;
}

bool stats::SpecialFlagsStat::isDead() const {
  return is_dead_;
}

void stats::SpecialFlagsStat::setImmortal(bool flag) {
  is_immortal_ = flag;
}

bool stats::SpecialFlagsStat::isImmortal() const {
  return is_immortal_;
}

stats::SymbolsStat::SymbolsStat(char dead, char undead) : dead_symbol_{dead}, undead_symbol_{undead} {}

void stats::SymbolsStat::setDeadSymbol(char c) {
  dead_symbol_ = c;
}

char stats::SymbolsStat::getDeadSymbol() const {
  return dead_symbol_;
}

void stats::SymbolsStat::setUndeadSymbol(char c) {
  undead_symbol_ = c;
}

bool stats::SymbolsStat::getUndeadSymbol() const {
  return undead_symbol_;
}

stats::CoordinateStat::CoordinateStat(Point p) : coordinate_{p} {}

stats::CoordinateStat::CoordinateStat(double row, double col) : coordinate_{row, col} {};

void stats::CoordinateStat::setCoord(Point p) {
  coordinate_ = p;
}

Point stats::CoordinateStat::getCoord() const {
  return coordinate_;
}

stats::HeroStat::HeroStat(int max_hp, int cur_hp,
                          int max_mp, int cur_mp,
                          int max_dp, int cur_dp,
                          int max_vp, int cur_vp,
                          bool is_dead, bool is_immortal,
                          char dead_symbol, char undead_symbol,
                          Point p) : HPStat(max_hp, cur_hp), MPStat(max_mp, cur_mp),
                                     DPStat(max_dp, cur_dp), VPStat(max_vp, cur_vp),
                                     SpecialFlagsStat(is_dead, is_immortal), SymbolsStat(dead_symbol, undead_symbol),
                                     CoordinateStat(p) {}
