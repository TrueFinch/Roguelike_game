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

actors::Hero::Hero(int damage, int mana, int health, actors::Point coord) {
  damage_points_ = damage;
  max_mana_points_ = mana;
  cur_mana_points_ = mana;
  max_health_points_ = health;
  cur_health_points_ = health;
  coord_ = coord;
  symbol_ = '@';
  is_dead_ = false;
  is_immortal_ = false;
}

void actors::Hero::setCoord(Point point) {
  coord_ = point;
}

void actors::Hero::collide(actors::Actor& _ca) {
  _ca.collide(*this);
}

void actors::Hero::collide(actors::Wall& _cw) {
  _cw.setCurHP(_cw.getCurHP() - getDamagePoints());
}

actors::Wall::Wall(int health, actors::Point coord) {
  max_health_points_ = health;
  cur_health_points_ = health;
  coord_ = coord;
  is_dead_ = false;
  is_immortal_ = false;
}