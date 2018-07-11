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

enums::CollideResult actor::ActiveActor::collide(Actor& other) {
  return other.collide(*this);
}

enums::CollideResult actor::ActiveActor::collide(PassiveActor& other) {
  return other.collide(*this);
}

enums::CollideResult actor::ActiveActor::collide(SpellActor& other) {
  return other.collide(*this);
}

enums::CollideResult actor::ActiveActor::collide(actor::CollectableActor& other) {
  return other.collide(*this);
}

void actor::ActiveActor::setIsDead(bool is_dead) {
  is_dead_ = is_dead;
}

bool actor::ActiveActor::getIsDead() const {
  return is_dead_;
}

void actor::ActiveActor::setIsImmortal(bool is_immortal) {
  is_immortal_ = is_immortal;
}

bool actor::ActiveActor::getIsImmortal() const {
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
  cur_mana_points_ = mp % max_mana_points_;
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
  while (cur_score_points_ >= max_score_points_) {
    this->upLevelPoints();
    cur_score_points_ -= max_score_points_;
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

Point actor::SpellActor::findTarget() {
  return this->getDirection();
}

enums::CollideResult actor::PassiveActor::collide(Actor& other) {
  return other.collide(*this);
}

enums::CollideResult actor::PassiveActor::collide(ActiveActor& other) {
  enums::CollideResult result = enums::FREE;
  enums::ActorID this_id = this->getID();
//  enums::ActorID other_id = other.getID();
  if (this_id == enums::WALL_ID) {
    result = enums::BARRIER;
  } else if (this_id == enums::FLOOR_ID) {
    result = enums::FREE;
  }
  return result;
}

enums::CollideResult actor::PassiveActor::collide(PassiveActor& other) {
  return enums::BARRIER;
}

enums::CollideResult actor::PassiveActor::collide(SpellActor& other) {
  enums::CollideResult result = enums::FREE;
  enums::ActorID this_id = this->getID();
  if (this_id == enums::WALL_ID) {
    result = enums::BARRIER;
  } else if ((this_id == enums::FLOOR_ID) or (this_id == enums::HP_POTION_ID) or (this_id == enums::MP_POTION_ID)) {
    result = enums::FREE;
  }
  return result;
}

enums::CollideResult actor::PassiveActor::collide(CollectableActor& other) {
  enums::CollideResult result = enums::FREE;
  enums::ActorID this_id = this->getID();
  if (this_id == enums::WALL_ID) {
    result = enums::BARRIER;
  } else if ((this_id == enums::FLOOR_ID) or (this_id == enums::HP_POTION_ID) or (this_id == enums::MP_POTION_ID)) {
    result = enums::FREE;
  }
  return result;
}

enums::CollideResult actor::CollectableActor::collide(ActiveActor& other) {
  enums::CollideResult result = enums::FREE;
  enums::ActorID this_id = this->getID();
  enums::ActorID other_id = other.getID();
  if ((this_id == enums::HP_POTION_ID) or (this_id == enums::MP_POTION_ID)) {
    if ((other_id == enums::HERO_ID) or (other_id == enums::PRINCESS_ID)) {
      result = enums::PICK;
    } else {
      result = enums::FREE;
    }
  }
  return result;
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


//std::shared_ptr<actor::ActiveActor> actor::ActiveActor::createActor(enums::ActorID id,
//                                                                    config::Config& config,
//                                                                    Point coord) {
//  std::shared_ptr<actor::ActiveActor> actor_ptr;
//
//  switch (id) {
//    case enums::ActorID::HERO_ID:
//      actor_ptr = std::make_shared<actor::Hero>(actor::Hero(config.getHeroStat(), coord));
//      break;
//    case enums::ActorID::ZOMBIE_ID:
//      actor_ptr = std::make_shared<actor::Zombie>(actor::Zombie(config.getZombieStat(), coord));
//      break;
//    case enums::ActorID::WALL_ID:
//      actor_ptr = std::make_shared<actor::Wall>(actor::Wall(config.getWallStat(), coord));
//      break;
//    case enums::ActorID::PRINCESS_ID:
//      actor_ptr = std::make_shared<actor::Princess>(actor::Princess(config.getPrincessStat(), coord));
//      break;
//    case enums::ActorID::DRAGON_ID:
//      actor_ptr = std::make_shared<actor::Dragon>(actor::Dragon(config.getDragonStat(), coord));
//      break;
//    case enums::ActorID::NOTHING_ID:
//      actor_ptr = nullptr;
//      break;
//    default:
//      assert(false);
//  }
//  return actor_ptr;
//}
