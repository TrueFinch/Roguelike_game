//
// Created by truefinch on 10.07.18.
//

#pragma once

#include <Actors.h>
#include <Enums.h>
#include <GameManager.h>

class Hero : public actor::ActiveActor {
 public:
  Hero(Point position, bool is_dead, bool is_immortal, char live_symbol, char dead_symbol, int max_hp,
       int cur_hp, int max_mp, int cur_mp, int dp, int vp, int lp, int max_sp, int cur_sp, int sp_multiplier)
      : ActiveActor(position, is_dead, is_immortal, "Hero", enums::HERO_ID, live_symbol, dead_symbol,
                    max_hp, cur_hp, max_mp, cur_mp, dp, vp, lp, max_sp, cur_sp, sp_multiplier) {};

  enums::CollideResult collide(Actor&) override;
  enums::CollideResult collide(ActiveActor&) override;
  enums::CollideResult collide(actor::PassiveActor&) override;
  enums::CollideResult collide(actor::SpellActor&) override;
  enums::CollideResult collide(actor::CollectableActor&) override;

  Point findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>&) override;
  Event doTurn() override;

  const std::vector<int> getStats() const;
  const std::vector<bool>& getAchievements() const;

  const int getHpPotionAmount() const;
  const int getMpPotionAmount() const;
 private:
  int zombie_killed_ = 0;
  int dragon_killed_ = 0;
  int steps_made_ = 0;
  int princess_rescued_ = 0;
  std::vector<bool> achievements_;

  int hp_potion_amount_ = 0;
  int mp_potion_amount_ = 0;
};

//TODO: add inventory
