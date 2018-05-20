//
// Created by truefinch on 20.05.18.
//

#ifndef ROGUELIKE_ACTOR_H
#define ROGUELIKE_ACTOR_H

namespace actors {

class Actor;
class ActiveActor;
class Hero;
class Princess;
class Zombie;
class Dragon;
class Wall;


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
  virtual void setCoord(Point) = 0;
  virtual Point getCoord() const = 0;
  virtual void setSymbol(char) = 0;
  virtual char getSymbol() const = 0;
  virtual void setMaxHP(int) = 0;
  virtual int getMaxHP() const = 0;
  virtual void setCurHP(int) = 0;
  virtual int getCurHP() const = 0;
  virtual void setDamagePoints(int) = 0;
  virtual int getDamagePoints() = 0;
  virtual bool isDead() const = 0;
  virtual void collide(Actor&) = 0;
  virtual void collide(Hero&) = 0;
//  virtual void collide(const Princess&) = 0;
//  virtual void collide(const Zombie&) = 0;
//  virtual void collide(const Dragon&) = 0;
//  virtual void collide(const PassiveActor&) = 0;
  virtual void collide(Wall&) = 0;
//  virtual void collide(const Potion&) = 0;
//  virtual void collide(const HealthP&) = 0;
//  virtual void collide(const ManaP&) = 0;
 protected:
  int damage_points_  = 0;
  int cur_mana_points_ = 0;
  int max_mana_points_ = 0;
  int cur_health_points_ = 0;
  int max_health_points_ = 0;
  char symbol_ = '$';
  bool is_dead_ = false;
  bool is_immortal_  = false;
  Point coord_ = {0, 0};
};

class Hero : Actor {
 public:
  Hero() = default;
  Hero(int damage, int mana, int health, Point coord);
  void setCoord(Point) override;
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Wall&) override;
};

class Wall : Actor {
 public:
  Wall() = default;
  Wall(int health, Point coord);
};
} // namespace actors

#endif //ROGUELIKE_ACTOR_H
