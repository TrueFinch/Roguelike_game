//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>
#include "GameManager.h"

class Princess : public actor::ActiveActor {
 public:
  Princess(Point position, bool is_dead, bool is_immortal, char live_symbol, char dead_symbol, int max_hp,
           int cur_hp, int max_mp, int cur_mp, int dp, int vp, int lp, int max_sp, int cur_sp, int sp_multiplier)
      : ActiveActor(position, is_dead, is_immortal, "Princess", enums::PRINCESS_ID, live_symbol, dead_symbol,
                    max_mp, cur_hp, max_mp, cur_mp, dp, vp, lp, max_sp, cur_sp, sp_multiplier) {};

  enums::CollideResult collide(Actor&) override;
  enums::CollideResult collide(ActiveActor&) override;
  enums::CollideResult collide(actor::PassiveActor&) override;
  Point findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>&) override;
  Event doTurn() override;
};


