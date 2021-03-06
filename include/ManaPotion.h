//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Actors.h>

class ManaPotion : public actor::CollectableActor {
 public:
  ManaPotion(Point position, char live_symbol, char dead_symbol, bool is_dead, bool is_immortal, int hp, int mp)
      : CollectableActor(position, "Mana potion", enums::MP_POTION_ID, live_symbol, dead_symbol, is_dead,
                         is_immortal, hp, mp) {}

  enums::CollideResult collide(actor::Actor&) override;
  enums::CollideResult collide(actor::ActiveActor&) override;
  enums::CollideResult collide(actor::PassiveActor&) override;
  enums::CollideResult collide(actor::SpellActor&) override;
  enums::CollideResult collide(actor::CollectableActor&) override;
};

