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

void actor::Actor::setSymbol(char symbol) {
  symbol_ = symbol;
}

char actor::Actor::getSymbol() const {
  return symbol_;
}

void actor::Actor::setIsImmortal(bool is_immortal) {
  is_immortal_ = is_immortal;
}

bool actor::Actor::getIsImmortal() const {
  return is_immortal_;
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

void actor::ActiveActor::setMaxHealthPoints(int hp) {
  max_health_points_ = hp;
}

int actor::ActiveActor::getMaxHealthPoints() const {
  return max_health_points_;
}

void actor::ActiveActor::setCurHealthPoints(int hp) {
  if (!this->is_dead_) {
    cur_health_points_ = hp % max_health_points_;
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

void actor::ActiveActor::setCurScorePoints(int sp) {
  cur_score_points_ = sp;
  while (cur_score_points_ >= max_score_points_) {
    this->upLevelPoints();
    this->setMaxHealthPoints(max_health_points_ + max_health_points_ * level_points_ / 10);
    this->setCurHealthPoints(max_health_points_);
    this->setMaxManaPoints(max_mana_points_ + max_mana_points_ * level_points_ / 10);
    this->setCurManaPoints(max_mana_points_);
    this->setMaxScorePoints(max_score_points_ + max_score_points_ * level_points_ / 10);
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

enums::CollideResult actor::Hero::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.getIsDead()) {
    result = enums::FREE;
  } else if (other_id == enums::HERO_ID) {
    result = enums::BARRIER;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID)) {
    result = enums::FIGHT;
  } else if (other_id == enums::PRINCESS_ID) {
    result = enums::WIN;
  }
  return result;
}

enums::CollideResult actor::Hero::move() {
  Point hero_pos = this->getPosition();
  auto area = game_manager_.getArea();
  int key = game_manager_.getLastPressedKey();
  Point dir = {0, 0};

  if (key == KEY_UP) {
    dir.x -= 1;
  } else if (key == KEY_DOWN) {
    dir.x += 1;
  } else if (key == KEY_LEFT) {
    dir.y -= 1;
  } else if (key == KEY_RIGHT) {
    dir.y += 1;
  }

  Point other_pos = {hero_pos.x + dir.x, hero_pos.y + dir.y};
  std::shared_ptr<Actor> other = area[other_pos.x][other_pos.y];
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER:
      break;
    case enums::FREE:
      game_manager_.swap(hero_pos, other_pos);
      break;
    case enums::FIGHT:
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(enemy->level_points_ * 10);
      if (enemy->getIsDead()) {
        game_manager_.swap(hero_pos, other_pos);
      } else {
        this->setCurHealthPoints(this->getCurHealthPoints() - enemy->getDamagePoints());
        enemy->setCurScorePoints(this->level_points_ * 10);
      }
      break;
    case enums::WIN:
      //do nothing
      break;
    case enums::PICK:
      if (other->getID() == enums::HP_POTION_ID)
        this->setCurHealthPoints(this->getCurHealthPoints() + this->getMaxHealthPoints() * this->getLevelPoints() / 10);
      else {
        this->setCurManaPoints(this->getCurManaPoints() + this->getMaxManaPoints() * this->getLevelPoints() / 10);
      }
  }

  return collision;
}

Point actor::Hero::findTarget() {
  return {42, 42};
}

enums::CollideResult actor::Zombie::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.getIsDead()) {
    result = enums::PICK;
  } else if ((other_id == enums::HERO_ID)) {
    result = enums::FIGHT;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID) or (other_id == enums::PRINCESS_ID)) {
    result = enums::BARRIER;
  }
  return result;
}

Point actor::Zombie::findTarget() {
//  auto area = game_manager_.getArea();
  return {rand() % 3 - 1, rand() % 3 - 1};
}

enums::CollideResult actor::Zombie::move() {
  Point zombie_pos = this->getPosition();
  auto area = game_manager_.getArea();
  Point dir = this->findTarget();
  Point other_pos = {zombie_pos.x + dir.x, zombie_pos.y + dir.y};
  std::shared_ptr<Actor> other = area[other_pos.x][other_pos.y];
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER:
      break;
    case enums::FREE:
      game_manager_.swap(zombie_pos, other_pos);
      break;
    case enums::FIGHT:
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(enemy->level_points_ * 10);
      if (enemy->getIsDead()) {
        game_manager_.swap(zombie_pos, other_pos);
      } else {
        this->setCurHealthPoints(this->getCurHealthPoints() - enemy->getDamagePoints());
        enemy->setCurScorePoints(this->level_points_ * 10);
      }
      break;
    case enums::WIN:
      //do nothing
      //this case is unreachable for zombie
      break;
    case enums::PICK:
      this->setCurHealthPoints(this->getCurHealthPoints() + this->getMaxHealthPoints() / 20);
      break;
  }
}

enums::CollideResult actor::Dragon::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if ((other_id == enums::HERO_ID)) {
    result = enums::FIGHT;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID) or (other_id == enums::PRINCESS_ID)) {
    result = enums::BARRIER;
  } else if (other.getIsDead()) {
    result = enums::FREE;
  }
  return result;
}

Point actor::Dragon::findTarget() {
//  auto area = game_manager_.getArea();
  return {rand() % 3 - 1, rand() % 3 - 1};
}

enums::CollideResult actor::Dragon::move() {
  Point dragon_pos = this->getPosition();
  auto area = game_manager_.getArea();
  Point dir = this->findTarget();
  Point other_pos = {dragon_pos.x + dir.x, dragon_pos.y + dir.y};
  std::shared_ptr<Actor> other = area[other_pos.x][other_pos.y];
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER:
      break;
    case enums::FREE:
      game_manager_.swap(dragon_pos, other_pos);
      break;
    case enums::FIGHT:
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(enemy->level_points_ * 10);
      if (enemy->getIsDead()) {
        game_manager_.swap(dragon_pos, other_pos);
      } else {
        this->setCurHealthPoints(this->getCurHealthPoints() - enemy->getDamagePoints());
        enemy->setCurScorePoints(this->level_points_ * 10);
      }
      break;
    case enums::WIN:
      //do nothing
      //this case is unreachable for Dragon too
      break;
    case enums::PICK:
      //Fireballs heal the Dragon
      this->setCurHealthPoints(this->getCurHealthPoints() + this->getMaxHealthPoints() / 20);
      break;
  }
}

enums::CollideResult actor::Princess::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if ((other_id == enums::FIRE_BALL_ID) or (other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID)) {
    result = enums::FIGHT;
  } else if ((other.getIsDead()) or (other_id == enums::PRINCESS_ID)) {
    result = enums::BARRIER;
  } else if (other_id == enums::HERO_ID) {
    result = enums::WIN;
  }
  return result;
}

Point actor::Princess::findTarget() {
//  auto area = game_manager_.getArea();
  return {rand() % 3 - 1, rand() % 3 - 1};
}

enums::CollideResult actor::Princess::move() {
  Point princess_pos = this->getPosition();
  auto area = game_manager_.getArea();
  Point dir = this->findTarget();
  Point other_pos = {princess_pos.x + dir.x, princess_pos.y + dir.y};
  std::shared_ptr<Actor> other = area[other_pos.x][other_pos.y];
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER:
      break;
    case enums::FREE:
      game_manager_.swap(princess_pos, other_pos);
      break;
    case enums::FIGHT:
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(enemy->level_points_ * 10);
      if (enemy->getIsDead()) {
        game_manager_.swap(princess_pos, other_pos);
      } else {
        this->setCurHealthPoints(this->getCurHealthPoints() - enemy->getDamagePoints());
        enemy->setCurScorePoints(this->level_points_ * 10);
      }
      break;
    case enums::WIN:
      //do nothing
      //this case is unreachable for Princess too
      break;
    case enums::PICK:
      if (other->getID() == enums::HP_POTION_ID)
        this->setCurHealthPoints(this->getCurHealthPoints() + this->getMaxHealthPoints() * this->getLevelPoints() / 10);
      else {
        this->setCurManaPoints(this->getCurManaPoints() + this->getMaxManaPoints() * this->getLevelPoints() / 10);
      }
  }

  return collision;
}

void actor::SpellActor::setDirection(Point dir) {
  direction_ = dir;
}

Point actor::SpellActor::getDirection() const {
  return direction_;
}

enums::CollideResult actor::Fireball::collide(actor::ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.getIsDead()) {
    result = enums::FREE;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::PRINCESS_ID) or (other_id == enums::HERO_ID)) {
    result = enums::FIGHT;
  } else if (other_id == enums::DRAGON_ID) {
    result = enums::PICK;
  }
  return result;
}

Point actor::SpellActor::findTarget() {
  return {42, 42};
}

enums::CollideResult actor::Fireball::move() {
  Point dragon_pos = this->getPosition();
  auto area = game_manager_.getArea();
  Point dir = this->findTarget();
  Point other_pos = {dragon_pos.x + dir.x, dragon_pos.y + dir.y};
  std::shared_ptr<Actor> other = area[other_pos.x][other_pos.y];
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER:
      break;
    case enums::FREE:
      game_manager_.swap(dragon_pos, other_pos);
      break;
    case enums::FIGHT:
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(enemy->level_points_ * 10);
      if (!this->getIsDead()) {
        if (enemy->getIsDead()) {
          game_manager_.swap(dragon_pos, other_pos);
        }
      }
      break;
    case enums::WIN:
      //do nothing
      //this case is unreachable for Fireball too
      break;
    case enums::PICK:
      //Fireballs heal the Dragon
      std::shared_ptr<actor::ActiveActor> dragon = std::static_pointer_cast<actor::ActiveActor>(other);
      this->setCurHealthPoints(this->getCurHealthPoints() + this->getMaxHealthPoints() / 20);
      break;
  }
}

enums::CollideResult actor::PassiveActor::collide(Actor& other) {
  return other.collide(*this);
}

enums::CollideResult actor::PassiveActor::collide(ActiveActor& other) {
  enums::CollideResult result = enums::FREE;
  enums::ActorID this_id = this->getID();
  enums::ActorID other_id = other.getID();
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
