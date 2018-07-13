//
// Created by truefinch on 13.07.18.
//

#include "Event.h"
#include <utility>

void Event::setExecutor(const std::string& ex) {
  this->executor_name_ = ex;
}

std::string Event::getExecutor() const {
  return executor_name_;
}

void Event::setTarget(const std::string& tr) {
  this->target_name = tr;
}

std::string Event::getTarget() const {
  return target_name;
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

Event::Event(std::string executor_name,
             std::string target_name,
             enums::TurnResult action,
             int value) : executor_name_{std::move(executor_name)}, target_name{std::move(target_name)}, action_{action}, value_{value} {}
