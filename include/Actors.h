//
// Created by truefinch on 20.05.18.
//

#ifndef ROGUELIKE_ACTOR_H
#define ROGUELIKE_ACTOR_H

namespace actor {

class Actor;
class ActiveActor;
class Hero;
class Princess;
class Zombie;
class Dragon;
class PassiveActor;
class Wall;
class Potion;
class HealthP;
class ManaP;


#define EPS 2e-15

struct Point {
  Point();
  Point(double x, double y);
  double x, y;
  const bool operator<(const Point& rhs) const;
  const bool operator==(const Point& rhs) const;
};

class Actor {
 public:
  Actor() = default;
  virtual Point getCoord() const = 0;
  virtual void setCoord() = 0;
  virtual bool isDead() const = 0;
  virtual Point move() = 0;
  virtual void collide(const Actor&) = 0;
  virtual void collide(const ActiveActor&) = 0;
  virtual void collide(const Hero&) = 0;
  virtual void collide(const Princess&) = 0;
  virtual void collide(const Zombie&) = 0;
  virtual void collide(const Dragon&) = 0;
  virtual void collide(const PassiveActor&) = 0;
  virtual void collide(const Wall&) = 0;
  virtual void collide(const Potion&) = 0;
  virtual void collide(const HealthP&) = 0;
  virtual void collide(const ManaP&) = 0;
 private:
  int damage_points_;
  int cur_health_points_;
  int max_health_points_;
  int cur_mana_points_;
  int max_mana_points_;
  char symbol_;
  bool is_dead_;
  Point coord_;
};

} // namespace actor

#endif //ROGUELIKE_ACTOR_H
