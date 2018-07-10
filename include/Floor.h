//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>

 class Floor : public actor::PassiveActor {
 public:
  Floor(Point position, bool is_immortal, char symbol)
      : PassiveActor(position, is_immortal, "Floor", enums::FLOOR_ID, symbol) {};
};
