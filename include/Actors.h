//
// Created by truefinch on 20.05.18.
//

#ifndef ROGUELIKE_ACTOR_H
#define ROGUELIKE_ACTOR_H

#include <memory>
#include <string>
#include <Statistics.h>
#include <Point.h>
#include <Config.h>
#include <Enums.h>

namespace actor {



class Actor;
class Hero;
class Zombie;
class Wall;
class Princess;
class Dragon;

class Actor {
 public:
  Actor() = default;
//  virtual void setCoord(Point) = 0;
  virtual void collide(Actor&) = 0;
  virtual void collide(Hero&) = 0;
  virtual void collide(Zombie&) = 0;
  virtual void collide(Wall&) = 0;
  virtual void collide(Princess&) = 0;
  virtual void collide(Dragon&) = 0;
//  virtual void collide(const Potion&) = 0;
//  virtual void collide(const HealthP&) = 0;
//  virtual void collide(const ManaP&) = 0;
    static std::shared_ptr<actor::Actor> createActor(enums::ActorID, config::Config&, Point);
    virtual ~Actor() = default;
};

class Hero : public stats::HeroStat, public Actor {
 public:
  Hero() = default;
  explicit Hero(std::shared_ptr<stats::HeroStat>, Point);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;
  void collide(Princess&) override;
  void collide(Dragon&) override;
};

class Zombie : public stats::ZombieStat, public Actor {
 public:
  Zombie() = default;
  explicit Zombie(std::shared_ptr<stats::ZombieStat>, Point);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;
  void collide(Princess&) override;
  void collide(Dragon&) override;
};

class Wall : public stats::WallStat, public Actor{
 public:
  Wall() = default;
  explicit Wall(std::shared_ptr<stats::WallStat>, Point);
  void collide(Actor&) override;
  void collide(Hero&) override;
  void collide(Zombie&) override;
  void collide(Wall&) override;
  void collide(Princess&) override;
  void collide(Dragon&) override;
};

 class Princess : public stats::PrincessStat, public Actor {
  public:
   Princess() = default;
   explicit Princess(std::shared_ptr<stats::PrincessStat>, Point);
   void collide(Actor&) override;
   void collide(Hero&) override;
   void collide(Zombie&) override;
   void collide(Wall&) override;
   void collide(Princess&) override;
   void collide(Dragon&) override;
 };

 class Dragon : public stats::DragonStat, public Actor {
  public:
   Dragon() = default;
   explicit Dragon(std::shared_ptr<stats::DragonStat>, Point);
   void collide(Actor&) override;
   void collide(Hero&) override;
   void collide(Zombie&) override;
   void collide(Wall&) override;
   void collide(Princess&) override;
   void collide(Dragon&) override;
 };

} // namespace actor

#endif //ROGUELIKE_ACTOR_H
