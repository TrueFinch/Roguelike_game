//
// Created by truefinch on 11.07.18.
//
#pragma once

#include <Enums.h>
#include <ncurses.h>
#include <vector>
#include <string>

class Loading {
 public:
  static Loading& Instance();
  enums::GameState update(int key);
  void setGreeting(const std::string&);
  std::string getGreeting();
  void setHint(const std::string&);
  std::string getHint();
 private:
  Loading() = default;
  ~Loading() = default;

  Loading(Loading const&) = delete;
  Loading& operator= (Loading const&) = delete;

  std::string greeting_;
  std::string hint_;
};

