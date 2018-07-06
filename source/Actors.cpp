//
// Created by truefinch on 20.05.18.
//

#include <Actors.h>
#include <cmath>
#include <cassert>
#include <utility>

std::shared_ptr<actor::Actor> actor::Actor::createActor(enums::ActorID id, config::Config& config, Point coord) {
  std::shared_ptr<actor::Actor> actor_ptr;

  switch (id) {
    case enums::ActorID::HERO_ID:
      actor_ptr = std::make_shared<actor::Hero>(actor::Hero(config.getHeroStat(), coord));
      break;
    case enums::ActorID::ZOMBIE_ID:
      actor_ptr = std::make_shared<actor::Zombie>(actor::Zombie(config.getZombieStat(), coord));
      break;
    case enums::ActorID::WALL_ID:
      actor_ptr = std::make_shared<actor::Wall>(actor::Wall(config.getWallStat(), coord));
      break;
    case enums::ActorID::PRINCESS_ID:
      actor_ptr =
          std::make_shared<actor::Princess>(actor::Princess(config.getPrincessStat(), coord));
      break;
    case enums::ActorID::DRAGON_ID:
      actor_ptr = std::make_shared<actor::Dragon>(actor::Dragon(config.getDragonStat(), coord));
      break;
    case enums::ActorID::NOTHING_ID:
      actor_ptr = nullptr;
      break;
    default:
      assert(false);
  }
  return actor_ptr;
}

actor::Hero::Hero(std::shared_ptr<stats::HeroStat> new_st, Point coord) {
//  std::shared_ptr<stats::HeroStat> new_st = std::dynamic_pointer_cast<stats::HeroStat>(st);
  this->setMaxHP(new_st->getMaxHP());
  this->setCurHP(new_st->getCurHP());
  this->setMaxMP(new_st->getMaxMP());
  this->setCurMP(new_st->getCurMP());
  this->setMaxDP(new_st->getMaxDP());
  this->setCurDP(new_st->getCurDP());
  this->setMaxVP(new_st->getMaxVP());
  this->setCurVP(new_st->getCurVP());
  this->setDead(new_st->isDead());
  this->setImmortal(new_st->isImmortal());
  this->setDeadSymbol(new_st->getDeadSymbol());
  this->setUndeadSymbol(new_st->getUndeadSymbol());
  this->setCoord(coord);
}

void actor::Hero::collide(actor::Actor& _ca) {
  _ca.collide(*this);
}

void actor::Hero::collide(actor::Hero& _ch) {}

void actor::Hero::collide(actor::Zombie& _cz) {
  this->setCurHP(this->getCurHP() - _cz.getCurDP());
  _cz.setCurHP(_cz.getCurHP() - this->getCurDP());
}

void actor::Hero::collide(actor::Wall& _cw) {
  _cw.setCurHP(_cw.getCurHP() - this->getCurDP());
}

void actor::Hero::collide(actor::Princess&) {
  //some win event
}

void actor::Hero::collide(actor::Dragon& _cd) {
  this->setCurHP(this->getCurHP() - _cd.getCurDP());
  _cd.setCurHP(_cd.getCurHP() - this->getCurDP());
}

actor::Zombie::Zombie(std::shared_ptr<stats::ZombieStat> new_st, Point coord) {
  this->setMaxHP(new_st->getMaxHP());
  this->setCurHP(new_st->getCurHP());
  this->setMaxDP(new_st->getMaxDP());
  this->setCurDP(new_st->getCurDP());
  this->setMaxVP(new_st->getMaxVP());
  this->setCurVP(new_st->getCurVP());
  this->setDead(new_st->isDead());
  this->setImmortal(new_st->isImmortal());
  this->setDeadSymbol(new_st->getDeadSymbol());
  this->setUndeadSymbol(new_st->getUndeadSymbol());
  this->setCoord(coord);
}

void actor::Zombie::collide(actor::Actor& _ca) {
  _ca.collide(*this);
}

void actor::Zombie::collide(actor::Hero& _ch) {
  _ch.collide(*this);
}

void actor::Zombie::collide(actor::Zombie& _cz) {}

void actor::Zombie::collide(actor::Wall& _cv) {}

void actor::Zombie::collide(actor::Princess&) {
  //do nothing
}

void actor::Zombie::collide(actor::Dragon&) {
  //do nothing
}

actor::Wall::Wall(std::shared_ptr<stats::WallStat> st, Point coord) {
  this->setMaxHP(st->getMaxHP());
  this->setCurHP(st->getCurHP());
  this->setDead(st->isDead());
  this->setImmortal(st->isImmortal());
  this->setDeadSymbol(st->getDeadSymbol());
  this->setUndeadSymbol(st->getUndeadSymbol());
  this->setCoord(coord);
}

void actor::Wall::collide(actor::Actor& _ca) {
  _ca.collide(*this);
}

void actor::Wall::collide(actor::Hero& _ch) {
  _ch.collide(*this);
}

void actor::Wall::collide(actor::Zombie& _cz) {
  _cz.collide(*this);
}

void actor::Wall::collide(actor::Wall&) {}

void actor::Wall::collide(actor::Princess&) {}

void actor::Wall::collide(actor::Dragon&) {
  //do nothing
}

actor::Princess::Princess(std::shared_ptr<stats::PrincessStat> new_st, Point coord) {
  this->setMaxMP(new_st->getMaxMP());
  this->setCurMP(new_st->getCurMP());
  this->setMaxVP(new_st->getMaxVP());
  this->setCurVP(new_st->getCurVP());
  this->setDead(new_st->isDead());
  this->setImmortal(new_st->isImmortal());
  this->setDeadSymbol(new_st->getDeadSymbol());
  this->setUndeadSymbol(new_st->getUndeadSymbol());
  this->setCoord(coord);
}

void actor::Princess::collide(actor::Actor& _ca) {
  _ca.collide(*this);
}

void actor::Princess::collide(actor::Hero& _ch) {
  _ch.collide(*this);
}

void actor::Princess::collide(actor::Zombie& _cz) {
  _cz.collide(*this);
}

void actor::Princess::collide(actor::Wall& _cw) {
  _cw.collide(*this);
}

void actor::Princess::collide(actor::Princess&) {
  //lol it's not possible
}

void actor::Princess::collide(actor::Dragon&) {
  //do nothing
}

actor::Dragon::Dragon(std::shared_ptr<stats::DragonStat> new_st, Point coord) {
  this->setMaxHP(new_st->getMaxHP());
  this->setCurHP(new_st->getCurHP());
  this->setMaxMP(new_st->getMaxMP());
  this->setCurMP(new_st->getCurMP());
  this->setMaxDP(new_st->getMaxDP());
  this->setCurDP(new_st->getCurDP());
  this->setMaxVP(new_st->getMaxVP());
  this->setCurVP(new_st->getCurVP());
  this->setDead(new_st->isDead());
  this->setImmortal(new_st->isImmortal());
  this->setDeadSymbol(new_st->getDeadSymbol());
  this->setUndeadSymbol(new_st->getUndeadSymbol());
  this->setCoord(coord);
}

void actor::Dragon::collide(actor::Actor& _ca) {
  _ca.collide(*this);
}

void actor::Dragon::collide(actor::Hero& _ch) {
  _ch.collide(*this);
}

void actor::Dragon::collide(actor::Zombie& _cz) {
  _cz.collide(*this);
}

void actor::Dragon::collide(actor::Wall& _cw) {
  _cw.collide(*this);
}

void actor::Dragon::collide(actor::Princess& _cp) {
  _cp.collide(*this);
}

void actor::Dragon::collide(actor::Dragon&) {
  //do nothing
}
