//
// Created by truefinch on 13.07.18.
//
#pragma once

#include <Actors.h>
#include <Point.h>
#include <memory>
#include <utility> #include <Enums.h>

class Event {
 public:
  Event(std::shared_ptr<actor::ActiveActor> executor,
        std::shared_ptr<actor::ActiveActor> target,
        enums::TurnResult action,
        int value) : executor_{std::move(executor)}, target_{std::move(target)}, action_{action}, value_{value} {};

  void setExecutor(const std::shared_ptr<actor::ActiveActor>&);
  std::shared_ptr<actor::ActiveActor> getExecutor() const;

  void setTarget(const std::shared_ptr<actor::ActiveActor>&);
  std::shared_ptr<actor::ActiveActor> getTarget() const;

  void setAction(const enums::TurnResult&);
  enums::TurnResult getAction() const;

  void setValue(const int&);
  int getValue() const;
 private:
  std::shared_ptr<actor::ActiveActor> executor_;
  std::shared_ptr<actor::ActiveActor> target_;
  enums::TurnResult action_;
  int value_;

};

