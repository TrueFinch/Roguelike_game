//
// Created by truefinch on 11.07.18.
//

#include "Wall.h"

enums::CollideResult Wall::collide(actor::Actor&) {
  return enums::BARRIER;
}

enums::CollideResult Wall::collide(actor::ActiveActor&) {
  return enums::BARRIER;
}

enums::CollideResult Wall::collide(actor::PassiveActor&) {
  return enums::BARRIER;
}
