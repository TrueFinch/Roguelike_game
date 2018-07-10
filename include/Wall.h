//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>

 class Wall : public actor::PassiveActor {
 public:
  Wall(Point position, char live_symbol, char dead_symbol)
      : PassiveActor(position, "Wall", enums::WALL_ID, live_symbol, dead_symbol) {};
};

