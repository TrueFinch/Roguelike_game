//
// Created by truefinch on 20.05.18.
// Without a clear specification
// Result becomes a mortification
//
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <Statistics.h>
#include <Point.h>
#include <Config.h>
#include <Enums.h>
#include <GameManager.h>

namespace actor {

class Actor;

class ActiveActor;

class Hero;

class Zombie;

class Princess;

class Dragon;

class SpellActor;

class Fireball;

class PassiveActor;

class Wall;

class Floor;

class CollectableActor;

class HealthPotion;

class ManaPotion;

class Actor {
 public:
  Actor(Point position, bool is_immortal, std::string name, enums::ActorID id, char symbol)
      : pos_{position}, is_immortal_{is_immortal}, name_{std::move(name)}, id_{id}, symbol_{symbol} {};
  virtual ~Actor() = default;

  virtual enums::CollideResult collide(Actor&) = 0;
  virtual enums::CollideResult collide(ActiveActor&) = 0;
  virtual enums::CollideResult collide(SpellActor&) = 0;
  virtual enums::CollideResult collide(PassiveActor&) = 0;
  virtual enums::CollideResult collide(CollectableActor&) = 0;

  void setPosition(Point);
  Point getPosition() const;
  void setSymbol(char);
  char getSymbol() const;
  void setIsImmortal(bool);
  bool getIsImmortal() const;
  std::string getName() const;
  enums::ActorID getID() const;

 protected:
  game::GameManager& game_manager_ = game::GameManager::Instance();
  Point pos_;
  bool is_immortal_;
  std::string name_;
  enums::ActorID id_;
  char symbol_;
};

class ActiveActor : public Actor {
 public:
  ActiveActor(Point position, bool is_dead, bool is_immortal, std::string name,
              enums::ActorID id, char symbol, int hp, int mp, int dp, int vp, int lp, int sp)
      : Actor(position, is_immortal, std::move(name), id, symbol),
        is_dead_{is_dead},
        max_health_points_{hp},
        cur_health_points_{hp},
        max_mana_points_{mp},
        cur_mana_points_{mp},
        damage_points_{dp},
        visibility_points_{vp},
        level_points_{lp},
        max_score_points_{sp},
        cur_score_points_{sp} {};
  ~ActiveActor() override = default;

  enums::CollideResult collide(Actor&) override;
  virtual enums::CollideResult collide(ActiveActor&) = 0;
  enums::CollideResult collide(PassiveActor&) override;
  enums::CollideResult collide(SpellActor&) override;
  enums::CollideResult collide(CollectableActor&) override;

  virtual Point findTarget() = 0;
  virtual enums::CollideResult move() = 0;

  void setIsDead(bool);
  bool getIsDead() const;
  void setMaxHealthPoints(int);
  int getMaxHealthPoints() const;
  void setCurHealthPoints(int);
  int getCurHealthPoints() const;
  void setMaxManaPoints(int);
  int getMaxManaPoints() const;
  void setCurManaPoints(int);
  int getCurManaPoints() const;
  void setDamagePoints(int);
  int getDamagePoints() const;
  void setVisibilityPoints(int);
  int getVisibilityPoints() const;
  void upLevelPoints();
  void downLevelPoints();
  int getLevelPoints() const;
  void setMaxScorePoints(int);
  int getMaxScorePoints() const;
  void setCurScorePoints(int);
  int getCurScorePoints() const;

//  static std::shared_ptr<actor::ActiveActor> createActor(enums::ActorID, config::Config&, Point);

 protected:
  bool is_dead_;
  int max_health_points_;
  int cur_health_points_;
  int max_mana_points_;
  int cur_mana_points_;
  int damage_points_;
  int visibility_points_;
  int level_points_;
  int max_score_points_;
  int cur_score_points_;
};

class Hero : public ActiveActor {
 public:
  Hero(Point position, bool is_dead, bool is_immortal, char symbol, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Hero", enums::HERO_ID, symbol, hp, mp, dp, vp, lp, sp) {};

  enums::CollideResult collide(ActiveActor&) override;

  Point findTarget() override;
  enums::CollideResult move() override;
};

class Zombie : public ActiveActor {
 public:
  Zombie(Point position, bool is_dead, bool is_immortal, char symbol, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Zombie", enums::ZOMBIE_ID, symbol, hp, mp, dp, vp, lp, sp) {};

  enums::CollideResult collide(ActiveActor&) override;
  Point findTarget() override;
  enums::CollideResult move() override;
};

class Dragon : public ActiveActor {
 public:
  Dragon(Point position, bool is_dead, bool is_immortal, char symbol, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Dragon", enums::DRAGON_ID, symbol, hp, mp, dp, vp, lp, sp) {};

  enums::CollideResult collide(ActiveActor&) override;
  Point findTarget() override;
  enums::CollideResult move() override;
};

class Princess : public ActiveActor {
 public:
  Princess(Point position, bool is_dead, bool is_immortal, char symbol, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Princess", enums::PRINCESS_ID, symbol, hp, mp, dp, vp, lp, sp) {};

  enums::CollideResult collide(ActiveActor&) override;
  Point findTarget() override;
  enums::CollideResult move() override;
};

class SpellActor : public ActiveActor {
 public:
  SpellActor(Point position, bool is_dead, bool is_immortal, std::string name, enums::ActorID id, char symbol,
             int hp, int mp, int dp, int vp, int lp, int sp, Point direction)
      : ActiveActor(position, is_dead, is_immortal, std::move(name), id, symbol, hp, mp, dp, vp, lp, sp),
        direction_{direction} {};

  virtual enums::CollideResult collide(ActiveActor&) = 0;
  Point findTarget() override;
  virtual enums::CollideResult move() = 0;

  void setDirection(Point);
  Point getDirection() const;

 protected:
  Point direction_;
};

class Fireball : public SpellActor {
  Fireball(Point position, bool is_dead, bool is_immortal, char symbol,
           int hp, int mp, int dp, int vp, int lp, int sp, Point direction)
      : SpellActor(position, is_dead, is_immortal, "Fireball", enums::FIRE_BALL_ID, symbol,
                   hp, mp, dp, vp, lp, sp, direction) {};

  enums::CollideResult collide(ActiveActor&) override;
  enums::CollideResult move() override;
};

class PassiveActor : public Actor {
 public:
  PassiveActor(Point position, bool is_immortal, std::string name, enums::ActorID id, char symbol)
      : Actor(position, is_immortal, std::move(name), id, symbol) {};
  ~PassiveActor() override = default;

  enums::CollideResult collide(Actor&) override;
  enums::CollideResult collide(ActiveActor&) override;
  enums::CollideResult collide(PassiveActor&) override;
  enums::CollideResult collide(SpellActor&) override;
  enums::CollideResult collide(CollectableActor&) override;
};

class Floor : public PassiveActor {
 public:
  Floor(Point position, bool is_immortal, char symbol)
      : PassiveActor(position, is_immortal, "Floor", enums::FLOOR_ID, symbol) {};
};

class Wall : public PassiveActor {
 public:
  Wall(Point position, bool is_immortal, char symbol)
      : PassiveActor(position, is_immortal, "Wall", enums::WALL_ID, symbol) {};
};

class CollectableActor : public PassiveActor {
 public:
  CollectableActor(Point position, bool is_immortal, std::string name, enums::ActorID id, char symbol, int hp, int mp)
      : PassiveActor(position, is_immortal, std::move(name), id, symbol) {};

  enums::CollideResult collide(ActiveActor&) override;
};

class HealthPotion : public CollectableActor {
  HealthPotion(Point position, char symbol, int hp, int mp)
      : CollectableActor(position, true, "Health potion", enums::HP_POTION_ID, symbol, hp, mp) {}
};

class ManaPotion : public CollectableActor {
  ManaPotion(Point position, char symbol, int hp, int mp)
      : CollectableActor(position, true, "Mana potion", enums::MP_POTION_ID, symbol, hp, mp) {}
};

} // namespace actor
