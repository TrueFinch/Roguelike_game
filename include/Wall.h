//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>

 class Wall : public actor::PassiveActor {
 public:
  Wall(Point position, bool is_immortal, char symbol)
      : PassiveActor(position, is_immortal, "Wall", enums::WALL_ID, symbol) {};
};

