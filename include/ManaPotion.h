//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>

 class ManaPotion : public actor::CollectableActor {
  ManaPotion(Point position, char symbol, int hp, int mp)
      : CollectableActor(position, true, "Mana potion", enums::MP_POTION_ID, symbol, hp, mp) {}
};

