//
// Created by truefinch on 27.05.18.
//

#include "Statistics.h"

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

void stats::FStat::setDead(bool flag) {
  is_dead_ = flag;
}

bool stats::FStat::isDead() const {
  return is_dead_;
}

void stats::FStat::setImmortal(bool flag) {
  is_immortal_ = flag;
}

bool stats::FStat::isImmortal() const {
  return is_immortal_;
}

void stats::SStat::setDeadSymbol(char c) {
  dead_symbol_ = c;
}

char stats::SStat::getDeadSymbol() const {
  return dead_symbol_;
}

void stats::SStat::setUndeadSymbol(char c) {
  undead_symbol_ = c;
}

bool stats::SStat::getUndeadSymbol() const {
  return undead_symbol_;
}

void stats::CStat::setCoord(Point p) {
  coordinate_ = p;
}

Point stats::CStat::getCoord() const {
  return coordinate_;
}
