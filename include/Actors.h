//
// Created by truefinch on 20.05.18.
// Without a clear specification
// Result becomes a mortification
//
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <Point.h>
#include <Enums.h>

namespace actor {

class Actor;

class ActiveActor;

class SpellActor;

class PassiveActor;

class CollectableActor;

class Actor {
 public:
  Actor(Point position, std::string name, enums::ActorID id, char live_symbol, char dead_symbol,
        int is_dead, int is_immortal)
      : pos_{position}, name_{std::move(name)},
        id_{id}, live_symbol_{live_symbol}, dead_symbol_{dead_symbol},
        is_dead_{is_dead},
        is_immortal_{is_immortal} {};
  virtual ~Actor() = default;

  virtual enums::CollideResult collide(Actor&) = 0;
  virtual enums::CollideResult collide(ActiveActor&) = 0;
  virtual enums::CollideResult collide(SpellActor&) = 0;
  virtual enums::CollideResult collide(PassiveActor&) = 0;
  virtual enums::CollideResult collide(CollectableActor&) = 0;

  void setPosition(Point);
  Point getPosition() const;
  void setLiveSymbol(char);
  char getLiveSymbol() const;
  void setDeadSymbol(char);
  char getDeadSymbol() const;
  std::string getName() const;
  enums::ActorID getID() const;

 protected:
  Point pos_;
  std::string name_;
  enums::ActorID id_;
  char live_symbol_;
  char dead_symbol_;
  int is_dead_;
  int is_immortal_;
};

class ActiveActor : public Actor {
 public:
  ActiveActor(Point position, bool is_dead, bool is_immortal, const std::string& name, enums::ActorID id,
              char live_symbol, char dead_symbol, int max_hp, int cur_hp, int max_mp, int cur_mp,
              int dp, int vp, int lp, int max_sp, int cur_sp, int sp_multiplier)
      : Actor(position, name, id, live_symbol, dead_symbol, is_dead, is_immortal),
        max_health_points_{max_hp},
        cur_health_points_{cur_hp},
        max_mana_points_{max_mp},
        cur_mana_points_{cur_mp},
        damage_points_{dp},
        visibility_points_{vp},
        level_points_{lp},
        max_score_points_{max_sp},
        cur_score_points_{cur_sp},
        score_points_multiplier{sp_multiplier} {};
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
  void setIsImmortal(bool);
  bool getIsImmortal() const;
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
  void setLevelPoints(int);
  void setMaxScorePoints(int);
  int getMaxScorePoints() const;
  void setCurScorePoints(int);
  int getCurScorePoints() const;
  void setScorePointsMultiplier(int);
  int getScorePointsMultiplier() const;

 protected:
  bool is_dead_;
  bool is_immortal_;
  int max_health_points_;
  int cur_health_points_;
  int max_mana_points_;
  int cur_mana_points_;
  int damage_points_;
  int visibility_points_;
  int level_points_ = 1;
  int max_score_points_;
  int cur_score_points_;
  int score_points_multiplier;
};

class SpellActor : public ActiveActor {
 public:
  SpellActor(Point position,
             bool is_dead,
             bool is_immortal,
             const std::string& name,
             enums::ActorID id,
             char live_symbol,
             char dead_symbol,
             int max_hp,
             int cur_hp,
             int max_mp,
             int cur_mp,
             int dp,
             int vp,
             int lp,
             int max_sp,
             int cur_sp,
             int sp_multiplier,
             Point direction)
      : ActiveActor(position, is_dead, is_immortal, name, id, live_symbol, dead_symbol,
                    max_hp, cur_hp, max_mp, cur_mp, dp, vp, lp, max_sp, cur_sp, sp_multiplier),
        direction_{direction} {};

  virtual enums::CollideResult collide(ActiveActor&) = 0;
  Point findTarget() override;
  virtual enums::CollideResult move() = 0;

  void setDirection(Point);
  Point getDirection() const;

 protected:
  Point direction_;
};

class PassiveActor : public Actor {
 public:
  PassiveActor(Point position, const std::string& name, enums::ActorID id, char live_symbol, char dead_symbol,
  bool is_dead, bool is_immortal)
      : Actor(position, name, id, live_symbol, dead_symbol, is_dead, is_immortal) {};
  ~PassiveActor() override = default;

  enums::CollideResult collide(Actor&) override;
  enums::CollideResult collide(ActiveActor&) override;
  enums::CollideResult collide(PassiveActor&) override;
  enums::CollideResult collide(SpellActor&) override;
  enums::CollideResult collide(CollectableActor&) override;
};

class CollectableActor : public PassiveActor {
 public:
  CollectableActor(Point position, const std::string& name, enums::ActorID id,
                   char live_symbol, char dead_symbol, bool is_dead, bool is_immortal, int hp, int mp)
      : PassiveActor(position, name, id, live_symbol, dead_symbol,  is_dead,  is_immortal),
        health_points_{hp}, mana_points_{mp} {};

  enums::CollideResult collide(ActiveActor&) override;

  void setHealthPoints(int);
  int getHealthPoints() const;
  void setManaPoints(int);
  int getManaPoints() const;
 private:
  int health_points_;
  int mana_points_;
};

} // namespace actor
