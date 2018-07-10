//
// Created by truefinch on 10.07.18.
//

#pragma once

#include <Actors.h>
#include <Enums.h>
#include "GameManager.h"

class Hero : public actor::ActiveActor {
 public:
  Hero(Point position, bool is_dead, bool is_immortal, char symbol, int hp, int mp, int dp, int vp, int lp, int sp)
      : ActiveActor(position, is_dead, is_immortal, "Hero", enums::HERO_ID, symbol, hp, mp, dp, vp, lp, sp) {};

  enums::CollideResult collide(ActiveActor&) override;

  Point findTarget() override;
  enums::CollideResult move() override;
};


