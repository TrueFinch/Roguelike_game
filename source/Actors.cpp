//
// Created by truefinch on 20.05.18.
//

#include <Actors.h>
#include <cmath>
#include <cassert>
#include <utility>

std::shared_ptr<actors::Actor> actors::Actor::createActor(actors::ActorID id, std::shared_ptr<stats::Statistics> st) {
  std::shared_ptr<actors::Actor> actor_ptr;

  switch (id) {
    case ActorID::HERO_ID:
      actor_ptr = std::make_shared<actors::Hero>(actors::Hero(std::dynamic_pointer_cast<stats::HeroStat>(st)));
      break;
    case ActorID::ZOMBIE_ID:
      actor_ptr = std::make_shared<actors::Zombie>(actors::Zombie(std::dynamic_pointer_cast<stats::ZombieStat>(st)));
      break;
    case ActorID::WALL_ID:
      actor_ptr = std::make_shared<actors::Wall>(actors::Wall(std::dynamic_pointer_cast<stats::WallStat>(st)));
      break;
    case ActorID::PRINCESS_ID:
      actor_ptr =
          std::make_shared<actors::Princess>(actors::Princess(std::dynamic_pointer_cast<stats::PrincessStat>(st)));
      break;
    case ActorID::DRAGON_ID:
      actor_ptr = std::make_shared<actors::Dragon>(actors::Dragon(std::dynamic_pointer_cast<stats::DragonStat>(st)));
      break;
//    default:
//      assert(false);
//    case PRINCESS_ID:break;
//    case DRAGON_ID:break;
  }
  return actor_ptr;
}

actors::Hero::Hero(std::shared_ptr<stats::HeroStat> new_st) {
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
  this->setCoord(new_st->getCoord());
}

void actors::Hero::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Hero::collide(actors::Hero& _ch) {}

void actors::Hero::collide(actors::Zombie& _cz) {
  this->setCurHP(this->getCurHP() - _cz.getCurDP());
  _cz.setCurHP(_cz.getCurHP() - this->getCurDP());
}

void actors::Hero::collide(actors::Wall& _cw) {
  _cw.setCurHP(_cw.getCurHP() - this->getCurDP());
}

void actors::Hero::collide(actors::Princess&) {
  //some win event
}

void actors::Hero::collide(actors::Dragon& _cd) {
  this->setCurHP(this->getCurHP() - _cd.getCurDP());
  _cd.setCurHP(_cd.getCurHP() - this->getCurDP());
}

actors::Zombie::Zombie(std::shared_ptr<stats::ZombieStat> new_st) {
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
  this->setCoord(new_st->getCoord());
}

void actors::Zombie::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Zombie::collide(actors::Hero& _ch) {
  _ch.collide(*this);
}

void actors::Zombie::collide(actors::Zombie& _cz) {}

void actors::Zombie::collide(actors::Wall& _cv) {}

void actors::Zombie::collide(actors::Princess&) {
  //do nothing
}

void actors::Zombie::collide(actors::Dragon&) {
  //do nothing
}

actors::Wall::Wall(std::shared_ptr<stats::WallStat> st) {
  this->setMaxHP(st->getMaxHP());
  this->setCurHP(st->getCurHP());
  this->setDead(st->isDead());
  this->setImmortal(st->isImmortal());
  this->setDeadSymbol(st->getDeadSymbol());
  this->setUndeadSymbol(st->getUndeadSymbol());
  this->setCoord(st->getCoord());
}

void actors::Wall::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Wall::collide(actors::Hero& _ch) {
  _ch.collide(*this);
}

void actors::Wall::collide(actors::Zombie& _cz) {
  _cz.collide(*this);
}

void actors::Wall::collide(actors::Wall&) {}

void actors::Wall::collide(actors::Princess&) {}

void actors::Wall::collide(actors::Dragon&) {
  //do nothing
}

actors::Princess::Princess(std::shared_ptr<stats::PrincessStat> new_st) {
  this->setMaxMP(new_st->getMaxMP());
  this->setCurMP(new_st->getCurMP());
  this->setMaxVP(new_st->getMaxVP());
  this->setCurVP(new_st->getCurVP());
  this->setDead(new_st->isDead());
  this->setImmortal(new_st->isImmortal());
  this->setDeadSymbol(new_st->getDeadSymbol());
  this->setUndeadSymbol(new_st->getUndeadSymbol());
  this->setCoord(new_st->getCoord());
}

void actors::Princess::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Princess::collide(actors::Hero& _ch) {
  _ch.collide(*this);
}

void actors::Princess::collide(actors::Zombie& _cz) {
  _cz.collide(*this);
}

void actors::Princess::collide(actors::Wall& _cw) {
  _cw.collide(*this);
}

void actors::Princess::collide(actors::Princess&) {
  //lol it's not possible
}

void actors::Princess::collide(actors::Dragon&) {
  //do nothing
}

actors::Dragon::Dragon(std::shared_ptr<stats::DragonStat> new_st) {
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
  this->setCoord(new_st->getCoord());
}

void actors::Dragon::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Dragon::collide(actors::Hero& _ch) {
  _ch.collide(*this);
}

void actors::Dragon::collide(actors::Zombie& _cz) {
  _cz.collide(*this);
}

void actors::Dragon::collide(actors::Wall& _cw) {
  _cw.collide(*this);
}

void actors::Dragon::collide(actors::Princess& _cp) {
  _cp.collide(*this);
}

void actors::Dragon::collide(actors::Dragon&) {
  //do nothing
}
