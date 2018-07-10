//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>


 class HealthPotion : public actor::CollectableActor {
  HealthPotion(Point position, char symbol, int hp, int mp)
      : CollectableActor(position, true, "Health potion", enums::HP_POTION_ID, symbol, hp, mp) {}
};
