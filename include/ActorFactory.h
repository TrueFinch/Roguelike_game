//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Config.h>
#include <Actors.h>
#include <Hero.h>
#include <Zombie.h>
#include <Dragon.h>
#include <Princess.h>
#include <Fireball.h>
#include <Wall.h>
#include <Floor.h>
#include <HealthPotion.h>
#include <ManaPotion.h>

namespace factory {

class ActorFactory {
 public:
  static ActorFactory& Instance();
  std::shared_ptr<actor::Actor> CreateActor(Point position, enums::ActorID);
 private:
  ActorFactory() = default;
  ~ActorFactory() = default;
  ActorFactory(ActorFactory const&) = delete;
  ActorFactory& operator= (ActorFactory const&) = delete;
};

} // namespace factory
