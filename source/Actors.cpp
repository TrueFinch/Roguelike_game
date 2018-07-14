//
// Created by truefinch on 20.05.18.
//

#include <Actors.h>
#include <cmath>
#include <cassert>
#include <utility>
#include <ncurses.h>

void actor::Actor::setPosition(Point position) {
  this->pos_ = position;
}

Point actor::Actor::getPosition() const {
  return this->pos_;
}

void actor::Actor::setLiveSymbol(char symbol) {
  live_symbol_ = symbol;
}

char actor::Actor::getLiveSymbol() const {
  return live_symbol_;
}

void actor::Actor::setDeadSymbol(char symbol) {
  dead_symbol_ = symbol;
}

char actor::Actor::getDeadSymbol() const {
  return dead_symbol_;
}

std::string actor::Actor::getName() const {
  return name_;
}

enums::ActorID actor::Actor::getID() const {
  return id_;
}

void actor::Actor::isDead(bool is_dead) {
  is_dead_ = is_dead;
}

bool actor::Actor::isDead() const {
  return is_dead_;
}

void actor::Actor::isImmortal(bool is_immortal) {
  is_immortal_ = is_immortal;
}

bool actor::Actor::isImmortal() const {
  return is_immortal_;
}

void actor::ActiveActor::setMaxHealthPoints(int hp) {
  max_health_points_ = hp;
}

int actor::ActiveActor::getMaxHealthPoints() const {
  return max_health_points_;
}

void actor::ActiveActor::setCurHealthPoints(int hp) {
  if (!this->is_dead_) {
    cur_health_points_ = (hp > max_health_points_) ? (max_health_points_) : (hp);
  }
  if ((cur_health_points_ <= 0) and (!this->is_immortal_)) {
    this->is_dead_ = true;
  }
}

int actor::ActiveActor::getCurHealthPoints() const {
  return cur_health_points_;
}

void actor::ActiveActor::setMaxManaPoints(int mp) {
  max_mana_points_ = mp;
}

int actor::ActiveActor::getMaxManaPoints() const {
  return max_mana_points_;
}

void actor::ActiveActor::setCurManaPoints(int mp) {
  if (mp > max_mana_points_) {
    cur_mana_points_ = max_mana_points_;
  } else {
    cur_mana_points_ = mp;
  }
}

int actor::ActiveActor::getCurManaPoints() const {
  return cur_mana_points_;
}

void actor::ActiveActor::setDamagePoints(int dp) {
  damage_points_ = dp;
}

int actor::ActiveActor::getDamagePoints() const {
  return damage_points_;
}

void actor::ActiveActor::setVisibilityPoints(int vp) {
  visibility_points_ = vp;
}

int actor::ActiveActor::getVisibilityPoints() const {
  return visibility_points_;
}

void actor::ActiveActor::upLevelPoints() {
  ++level_points_;
  this->setMaxHealthPoints(max_health_points_ + max_health_points_ * level_points_ / 10);
  this->setCurHealthPoints(max_health_points_);
  this->setMaxManaPoints(max_mana_points_ + max_mana_points_ * level_points_ / 10);
  this->setCurManaPoints(max_mana_points_);
  this->setMaxScorePoints(max_score_points_ + max_score_points_ * level_points_ / 10);
}

void actor::ActiveActor::downLevelPoints() {
  if (level_points_ > 0) {
    (--level_points_);
  } else {
    level_points_ = 1;
  }
}

int actor::ActiveActor::getLevelPoints() const {
  return level_points_;
}

void actor::ActiveActor::setLevelPoints(int lp) {
  for(int i = level_points_; i < lp; ++i) {
    this->upLevelPoints();
  }
}

void actor::ActiveActor::setCurScorePoints(int sp) {
  cur_score_points_ = sp;
  while (cur_score_points_ > max_score_points_) {
    cur_score_points_ -= max_score_points_;
    this->upLevelPoints();
  }
}

int actor::ActiveActor::getCurScorePoints() const {
  return cur_score_points_;
}

void actor::ActiveActor::setMaxScorePoints(int sp) {
  max_score_points_ = sp;
}

int actor::ActiveActor::getMaxScorePoints() const {
  return max_score_points_;
}

void actor::ActiveActor::setScorePointsMultiplier(int sp_multiplier) {
  score_points_multiplier = sp_multiplier;
}

int actor::ActiveActor::getScorePointsMultiplier() const {
  return score_points_multiplier;
}

void actor::SpellActor::setDirection(Point dir) {
  direction_ = dir;
}

Point actor::SpellActor::getDirection() const {
  return direction_;
}

Point actor::SpellActor::findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>& area) {
  return this->getDirection();
}

void actor::CollectableActor::setHealthPoints(int hp) {
  health_points_ = hp;
}

int actor::CollectableActor::getHealthPoints() const {
  return health_points_;
}

void actor::CollectableActor::setManaPoints(int mp) {
  mana_points_ = mp;
}

int actor::CollectableActor::getManaPoints() const {
  return mana_points_;
}
