//
// Created by truefinch on 10.07.18.
//

#pragma once

#include <Actors.h>
#include <Enums.h>
#include "GameManager.h"

class Hero : public actor::ActiveActor {
 public:
  Hero(Point position, bool is_dead, bool is_immortal, char live_symbol, char dead_symbol,
       int max_hp, int cur_hp, int max_mp, int cur_mp, int dp, int vp, int lp, int max_sp, int cur_sp)
      : ActiveActor(position, is_dead, is_immortal, "Hero", enums::HERO_ID, live_symbol, dead_symbol,
                    max_hp, cur_hp, max_mp, cur_mp, dp, vp, lp, max_sp, cur_sp) {};

  enums::CollideResult collide(ActiveActor&) override;

  Point findTarget() override;
  enums::CollideResult move() override;
};


