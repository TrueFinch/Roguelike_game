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
  Actor(Point position, bool is_immortal, std::string name, enums::ActorID id)
      : pos_{position}, is_immortal_{is_immortal}, name_{std::move(name)}, id_{id} {};
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
  Point pos_;
  bool is_immortal_;
  std::string name_;
  enums::ActorID id_;
};

class ActiveActor : public Actor {
 public:
  ActiveActor(Point position, bool is_dead, bool is_immortal, std::string name,
              enums::ActorID id, int hp, int mp, int dp, int vp, int lp)
      : Actor(position, is_immortal, std::move(name), id),
        is_dead_{is_dead},
        max_health_points_{hp},
        cur_health_points_{hp},
        max_mana_points_{mp},
        cur_mana_points_{mp},
        max_damage_points_{dp},
        cur_damage_points_{dp},
        max_visibility_points_{vp},
        cur_visibility_points_{vp},
        max_level_points_{lp},
        cur_level_points_{lp} {};
  ~ActiveActor() override = default;

  enums::CollideResult collide(Actor&) override;
  virtual enums::CollideResult collide(ActiveActor&) = 0;
  enums::CollideResult collide(PassiveActor&) override;
  enums::CollideResult collide(SpellActor&) override;
  enums::CollideResult collide(CollectableActor&) override;

  void setIsDead(bool);
  bool getIsDead() const;

  static std::shared_ptr<actor::ActiveActor> createActor(enums::ActorID, config::Config&, Point);

 protected:
  bool is_dead_;
  int max_health_points_;
  int cur_health_points_;
  int max_mana_points_;
  int cur_mana_points_;
  int max_damage_points_;
  int cur_damage_points_;
  int max_visibility_points_;
  int cur_visibility_points_;
  int max_level_points_;
  int cur_level_points_;
};

class Hero : public ActiveActor {
 public:
  Hero(Point position, bool is_dead, bool is_immortal, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Hero", enums::HERO_ID, hp, mp, dp, vp, lp),
        max_score_points{sp},
        cur_score_points{sp} {};

  enums::CollideResult collide(ActiveActor&) override;

 private:
  int max_score_points;
  int cur_score_points;
};

class Zombie : public ActiveActor {
 public:
  Zombie(Point position, bool is_dead, bool is_immortal, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Zombie", enums::ZOMBIE_ID, hp, mp, dp, vp, lp) {};

  enums::CollideResult collide(ActiveActor&) override;
};

class Dragon : public ActiveActor {
 public:
  Dragon(Point position, bool is_dead, bool is_immortal, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Dragon", enums::DRAGON_ID, hp, mp, dp, vp, lp) {};

  enums::CollideResult collide(ActiveActor&) override;
};

class Princess : public ActiveActor {
 public:
  Princess(Point position, bool is_dead, bool is_immortal, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Princess", enums::PRINCESS_ID, hp, mp, dp, vp, lp) {};

  enums::CollideResult collide(ActiveActor&) override;
};

class SpellActor : public ActiveActor {
 public:
  SpellActor(Point position, bool is_dead, bool is_immortal, std::string name, enums::ActorID id,
             int hp, int mp, int dp, int vp, int lp, Point direction)
      : ActiveActor(position, is_dead, is_immortal, std::move(name), id, hp, mp, dp, vp, lp),
        direction_{direction} {};

  virtual enums::CollideResult collide(ActiveActor&) = 0;

  void setDirection(Point);
  Point getDirection() const;

 protected:
  Point direction_;
};

class Fireball : public SpellActor {
  Fireball(Point position, bool is_dead, bool is_immortal, int hp, int mp, int dp, int vp, int lp, Point direction)
      : SpellActor(position, is_dead, is_immortal, "Fireball", enums::FIRE_BALL_ID, hp, mp, dp, vp, lp, direction) {};

  enums::CollideResult collide(ActiveActor&) override;
};

class PassiveActor : public Actor {
 public:
  PassiveActor(Point position, bool is_immortal, std::string name, enums::ActorID id)
      : Actor(position, is_immortal, std::move(name), id) {};
  ~PassiveActor() override = default;

  enums::CollideResult collide(Actor&) override;
  virtual enums::CollideResult collide(ActiveActor&) = 0;
  enums::CollideResult collide(PassiveActor&) override;
  enums::CollideResult collide(SpellActor&) override;
  enums::CollideResult collide(CollectableActor&) override;
};

class Floor : public PassiveActor {
 public:
  Floor(Point position, bool is_immortal)
      : PassiveActor(position, is_immortal, "Floor", enums::FLOOR_ID) {};

  enums::CollideResult collide(ActiveActor&) override;
};

class Wall : public PassiveActor {
 public:
  Wall(Point position)
      : PassiveActor(position, true, "Wall", enums::WALL_ID) {};

  enums::CollideResult collide(ActiveActor&) override;
};

class CollectableActor : public PassiveActor {
 public:
  CollectableActor(Point position, bool is_immortal, std::string name, enums::ActorID id, int hp, int mp)
      : PassiveActor(position, is_immortal, std::move(name), id),
        max_health_points_{hp}, cur_health_points_{hp},
        max_mana_points_{mp}, cur_mana_points_{mp} {};

  virtual enums::CollideResult collide(ActiveActor&) = 0;

 protected:
  int max_health_points_;
  int cur_health_points_;
  int max_mana_points_;
  int cur_mana_points_;
};

class HealthPotion : public CollectableActor {
  HealthPotion(Point position, int hp, int mp)
      : CollectableActor(position, true, "Health potion", enums::HP_POTION_ID, hp, mp) {}

  enums::CollideResult collide(ActiveActor&) override;
};

class ManaPotion : public CollectableActor {
  ManaPotion(Point position, int hp, int mp)
      : CollectableActor(position, true, "Mana potion", enums::MP_POTION_ID, hp, mp) {}

  enums::CollideResult collide(ActiveActor&) override;
};

} // namespace actor
