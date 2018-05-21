//
// Created by truefinch on 20.05.18.
//

#ifndef ROGUELIKE_ACTOR_H
#define ROGUELIKE_ACTOR_H

#include <memory>
#include <map>
#include <string>

namespace actors {

enum ActorID {HERO_ID = 0, PRINCESS_ID, ZOMBIE_ID, DRAGON_ID, WALL_ID};

class Actor;
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
  void setCoord(Point);
  Point getCoord() const;
  void setLsymbol(char);
  char getLsymbol() const;
  void setDsymbol(char);
  char getDsymbol() const;
  void setMaxHP(int);
  int getMaxHP() const;
  void setCurHP(int);
  int getCurHP() const;
  void setMaxMP(int);
  int getMaxMP() const;
  void setCurMP(int);
  int getCurMP() const;
  void setDamagePoints(int);
  int getDamagePoints();
  bool isDead() const;
  bool isImmortal() const;
  virtual void collide(Actor&) = 0;
  virtual void collide(Hero&) = 0;
//  virtual void collide(const Princess&) = 0;
  virtual void collide(Zombie&) = 0;
//  virtual void collide(const Dragon&) = 0;
//  virtual void collide(const PassiveActor&) = 0;
  virtual void collide(Wall&) = 0;
//  virtual void collide(const Potion&) = 0;
//  virtual void collide(const HealthP&) = 0;
//  virtual void collide(const ManaP&) = 0;
    static std::shared_ptr<actors::Actor> createActor(actors::ActorID id, std::map<char, int> args);
 protected:
  int damage_points_ = 0;
  int cur_mana_points_ = 0;
  int max_mana_points_ = 0;
  int cur_health_points_ = 0;
  int max_health_points_ = 0;
  int visibility = 0;
  char lsymbol_ = '$';
  char dsymbol_ = '$';
  bool is_dead_ = false;
  bool is_immortal_ = false;
  Point coord_ = {0, 0};
};

class Hero : Actor {
 public:
  Hero() = default;
  Hero(int damage, int mana, int health, Point coord);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;
};

class Zombie : Actor {
 public:
  Zombie() = default;
  Zombie(int damage, int health, Point coord);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;

};

class Wall : Actor {
 public:
  Wall() = default;
  Wall(int health, Point coord);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;  
  void collide(Wall&) override;
};
} // namespace actors

#endif //ROGUELIKE_ACTOR_H
