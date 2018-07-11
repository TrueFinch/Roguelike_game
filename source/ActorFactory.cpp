//
// Created by truefinch on 11.07.18.
//

#include "ActorFactory.h"

factory::ActorFactory& factory::ActorFactory::Instance() {
  static ActorFactory self;
  return self;
}
