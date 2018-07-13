//
// Created by truefinch on 11.07.18.
//

#include "Floor.h"

enums::CollideResult Floor::collide(actor::Actor&) {
  return enums::FREE;
}

enums::CollideResult Floor::collide(actor::ActiveActor&) {
  return enums::FREE;
}

enums::CollideResult Floor::collide(actor::PassiveActor&) {
  return enums::FREE;
}
