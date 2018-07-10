//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>
#include "GameManager.h"

class Fireball : public actor::SpellActor {
  Fireball(Point position, bool is_dead, bool is_immortal, char live_symbol, char dead_symbol,
           int hp, int mp, int dp, int vp, int lp, int sp, Point direction)
      : SpellActor(position, is_dead, is_immortal, "Fireball", enums::FIRE_BALL_ID, live_symbol, dead_symbol,
                   hp, mp, dp, vp, lp, sp, direction) {};

  enums::CollideResult collide(ActiveActor&) override;
  enums::CollideResult move() override;
};