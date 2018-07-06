//
// Created by truefinch on 21.05.18.
//

#pragma once

#include <Actors.h>
#include <vector>
#include <cstring>
#include <memory>
#include <Config.h>

namespace map {

class Cell {
 public:
  Cell() = default;
  explicit Cell(std::shared_ptr<actor::Actor> ptr);
  void setPointer(std::shared_ptr<actor::Actor>);
  std::shared_ptr<actor::Actor> getPointer() const;
 private:
  std::shared_ptr<actor::Actor> ptr_;
};

class Map {
 public:
  Map() = default;
//  Map();
  void loadMap(config::Config&);
//  std::vector<std::string> getArea(const actor::Point& coord, const int radius) const;
 private:
  std::vector<actor::Actor> actors_;
  std::vector<std::vector<map::Cell>> board_;
};

} // namespace map
