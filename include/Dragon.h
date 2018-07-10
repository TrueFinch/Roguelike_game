//
// Created by truefinch on 10.07.18.
//
#pragma once

#include <Actors.h>
#include "GameManager.h"

 class Dragon : public actor::ActiveActor {
 public:
  Dragon(Point position, bool is_dead, bool is_immortal, char symbol, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Dragon", enums::DRAGON_ID, symbol, hp, mp, dp, vp, lp, sp) {};

  enums::CollideResult collide(ActiveActor&) override;
  Point findTarget() override;
  enums::CollideResult move() override;
};
