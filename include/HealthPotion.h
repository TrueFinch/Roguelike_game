//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>

class HealthPotion : public actor::CollectableActor {
 public:
  HealthPotion(Point position, char live_symbol, char dead_symbol, bool is_dead, bool is_immortal, int hp, int mp)
      : CollectableActor(position,
                         "Health potion",
                         enums::HP_POTION_ID,
                         live_symbol,
                         dead_symbol,
                         is_dead,
                         is_immortal,
                         hp,
                         mp) {}
};
