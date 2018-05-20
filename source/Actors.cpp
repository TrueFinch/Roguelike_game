//
// Created by truefinch on 20.05.18.
//

#include <Actors.h>
#include <cmath>

actors::Point::Point() {
  this->x = 42.0;
  this->y = 42.0;
}

actors::Point::Point(double x, double y) : x{x}, y{y} {}

const bool actors::Point::operator<(const Point& rhs) const {
  return ((this->x < rhs.x) && (this->y < rhs.y));
}

const bool actors::Point::operator==(const Point& rhs) const {
  return ((fabs(this->x - rhs.x) <= EPS) && (fabs(this->y - rhs.y) <= EPS));
}

void actors::Actor::setCoord(actors::Point p) {
  coord_ = p;
}

actors::Point actors::Actor::getCoord() const {
  return coord_;
}

void actors::Actor::setLsymbol(char c) {
  lsymbol_ = c;
}

char actors::Actor::getLsymbol() const {
  return lsymbol_;
}

void actors::Actor::setDsymbol(char c) {
  dsymbol_ = c;
}

char actors::Actor::getDsymbol() const {
  return dsymbol_;
}

void actors::Actor::setMaxHP(int hp) {
  max_health_points_ = hp;
}

int actors::Actor::getMaxHP() const {
  return max_health_points_;
}

void actors::Actor::setCurHP(int hp) {
  cur_health_points_ = hp;
}

int actors::Actor::getCurHP() const {
  return cur_health_points_;
}

void actors::Actor::setMaxMP(int mp) {
  max_mana_points_ = mp;
}

int actors::Actor::getMaxMP() const {
  return max_mana_points_;
}

void actors::Actor::setCurMP(int mp) {
  cur_mana_points_ = mp;
}

int actors::Actor::getCurMP() const {
  return cur_mana_points_;
}

void actors::Actor::setDamagePoints(int d) {
  damage_points_ = d;
}

int actors::Actor::getDamagePoints() {
  return damage_points_;
}

bool actors::Actor::isDead() const {
  return is_dead_;
}

bool actors::Actor::isImmortal() const {
  return is_immortal_;
}

actors::Hero::Hero(int damage, int mana, int health, actors::Point coord) {
  damage_points_ = damage;
  max_mana_points_ = mana;
  cur_mana_points_ = mana;
  max_health_points_ = health;
  cur_health_points_ = health;
  coord_ = coord;
  lsymbol_ = '@';
  dsymbol_ = '~';
  is_dead_ = false;
  is_immortal_ = false;
}

void actors::Hero::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Hero::collide(actors::Hero& _ch) {}

void actors::Hero::collide(actors::Zombie& _cz) {
  setCurHP(getCurHP() - _cz.getDamagePoints());
  _cz.setCurHP(_cz.getCurHP() - getDamagePoints());
}

void actors::Hero::collide(actors::Wall& _cw) {
  _cw.setCurHP(_cw.getCurHP() - getDamagePoints());
}

actors::Zombie::Zombie(int damage, int health, actors::Point coord) {
  damage_points_ = damage;
  max_health_points_ = health;
  cur_health_points_ = health;
  coord_ = coord;
  lsymbol_ = 'z';
  dsymbol_ = '+';
  is_dead_ = false;
  is_immortal_ = false;
}

void actors::Zombie::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Zombie::collide(actors::Hero& _ch) {
  _ch.collide(*this);
}

void actors::Zombie::collide(actors::Zombie& _cz) {}

void actors::Zombie::collide(actors::Wall& _cv) {}

actors::Wall::Wall(int health, actors::Point coord) {
  max_health_points_ = health;
  cur_health_points_ = health;
  coord_ = coord;
  is_dead_ = false;
  is_immortal_ = false;
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