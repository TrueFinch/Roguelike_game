//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>
#include "GameManager.h"

 class Princess : public actor::ActiveActor {
 public:
  Princess(Point position, bool is_dead, bool is_immortal, char live_symbol, char dead_symbol,
           int max_hp, int cur_hp, int max_mp, int cur_mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Princess", enums::PRINCESS_ID, live_symbol, dead_symbol,
                    max_mp, cur_hp, max_mp, cur_mp, dp, vp, lp, sp, 0) {};

  enums::CollideResult collide(ActiveActor&) override;
  Point findTarget() override;
  enums::CollideResult move() override;
};


