//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>

 class Floor : public actor::PassiveActor {
 public:
  Floor(Point position, char live_symbol, char dead_symbol, bool is_dead, bool is_immortal)
      : PassiveActor(position, "Floor", enums::FLOOR_ID, live_symbol, dead_symbol,  is_dead,  is_immortal) {};
};
