//
// Created by truefinch on 13.07.18.
//
#pragma once

#include <Point.h>
#include <memory>
#include <utility>
#include <Enums.h>

class Event;

namespace actor {
class ActiveActor;
}

class Event {
 public:
  Event() = default;
  Event(std::string executor_name,
        std::string target_name,
        enums::TurnResult action,
        int value);

  void setExecutor(const std::string&);
  std::string getExecutor() const;

  void setTarget(const std::string&);
  std::string getTarget() const;

  void setAction(const enums::TurnResult&);
  enums::TurnResult getAction() const;

  void setValue(const int&);
  int getValue() const;
 private:
  std::string executor_name_;
  std::string target_name;
  enums::TurnResult action_;
  int value_;

};

