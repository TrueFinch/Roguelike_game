//
// Created by truefinch on 11.07.18.
//

#include "HealthPotion.h"

enums::CollideResult HealthPotion::collide(actor::Actor& other) {
  return other.collide(*this);
}

enums::CollideResult HealthPotion::collide(actor::ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if ((other_id == enums::HERO_ID) or (other_id == enums::PRINCESS_ID)) {
    result = enums::PICK;
  } else {
    result = enums::FREE;
  }
  return result;
}

enums::CollideResult HealthPotion::collide(actor::PassiveActor&) {
  return enums::FREE;
}

enums::CollideResult HealthPotion::collide(actor::SpellActor&) {
  return enums::FREE;
}

enums::CollideResult HealthPotion::collide(actor::CollectableActor&) {
  return enums::FREE;
}