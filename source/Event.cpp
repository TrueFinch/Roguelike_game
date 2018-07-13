//
// Created by truefinch on 13.07.18.
//

#include "Event.h"

void Event::setExecutor(const std::shared_ptr<actor::ActiveActor>& ex) {
  this->executor_ = ex;
}

std::shared_ptr<actor::ActiveActor> Event::getExecutor() const {
  return executor_;
}

void Event::setTarget(const std::shared_ptr<actor::ActiveActor>& tr) {
  this->target_ = tr;
}

std::shared_ptr<actor::ActiveActor> Event::getTarget() const {
  return target_;
}

void Event::setAction(const enums::TurnResult& action) {
  this->action_ = action;
}

enums::TurnResult Event::getAction() const {
  return this->action_;
}

void Event::setValue(const int& val) {
  this->value_ = val;
}

int Event::getValue() const {
  return this->value_;
}
