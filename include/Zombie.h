//
// Created by truefinch on 10.07.18.
//
#pragma once

#include <Actors.h>
#include "GameManager.h"

class Zombie : public actor::ActiveActor {
 public:
  Zombie(Point position, bool is_dead, bool is_immortal, char live_symbol, char dead_symbol, int max_hp,
         int cur_hp, int max_mp, int cur_mp, int dp, int vp, int lp, int max_sp, int cur_sp, int sp_multiplier)
      : ActiveActor(position, is_dead, is_immortal, "Zombie", enums::ZOMBIE_ID, live_symbol, dead_symbol,
                    max_hp, cur_hp, max_mp, cur_mp, dp, vp, lp, max_sp, cur_sp, sp_multiplier) {};

  enums::CollideResult collide(actor::Actor&) override;
  enums::CollideResult collide(actor::ActiveActor&) override;
  enums::CollideResult collide(actor::PassiveActor&) override;
  Point findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>&) override;
  Event doTurn() override;
};
