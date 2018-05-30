//
// Created by truefinch on 20.05.18.
//

#ifndef ROGUELIKE_ACTOR_H
#define ROGUELIKE_ACTOR_H

#include <memory>
#include <map>
#include <string>
#include <Statistics.h>
#include <Point.h>

namespace actors {

enum ActorID {HERO_ID = '@', ZOMBIE_ID = 'z', WALL_ID = '#', PRINCESS_ID = '*', DRAGON_ID = 'D'};

class Actor;
class Hero;
class Zombie;
class Wall;
class Princess;
//class Dragon;

class Actor {
 public:
  Actor() = default;
  virtual void collide(Actor&) = 0;
  virtual void collide(Hero&) = 0;
  virtual void collide(Princess&) = 0;
  virtual void collide(Zombie&) = 0;
//  virtual void collide(const Dragon&) = 0;
//  virtual void collide(const PassiveActor&) = 0;
  virtual void collide(Wall&) = 0;
//  virtual void collide(const Potion&) = 0;
//  virtual void collide(const HealthP&) = 0;
//  virtual void collide(const ManaP&) = 0;
    static std::shared_ptr<actors::Actor> createActor(actors::ActorID id, std::shared_ptr<stats::Statistics> st);
    virtual ~Actor() = default;
};

class Hero : public stats::HeroStat, public Actor {
 public:
  Hero() = default;
  explicit Hero(std::shared_ptr<stats::HeroStat>);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;
  void collide(Princess&) override;
};

class Zombie : public stats::ZombieStat, public Actor {
 public:
  Zombie() = default;
  explicit Zombie(std::shared_ptr<stats::ZombieStat>);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;
  void collide(Princess&) override;
};

class Wall : public stats::WallStat, public Actor{
 public:
  Wall() = default;
  explicit Wall(std::shared_ptr<stats::WallStat>);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;
  void collide(Princess&) override;
};

 class Princess : public stats::PrincessStat, public Actor {
  public:
   Princess() = default;
   explicit Princess(std::shared_ptr<stats::PrincessStat>);
   void collide(Actor&) override;
   void collide(Hero&) override;
   void collide(Zombie&) override;
   void collide(Wall&) override;
   void collide(Princess&) override;
 };

} // namespace actors

#endif //ROGUELIKE_ACTOR_H
