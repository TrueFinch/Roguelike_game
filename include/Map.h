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
  std::shared_ptr<actor::Hero> loadMap(std::vector<std::shared_ptr<actor::Actor>>& npc, config::Config&);
//  std::vector<std::string> getArea(const actor::Point& coord, const int radius) const;
  std::shared_ptr<std::vector<std::string>> getMapView() const;
 private:
  std::vector<std::vector<map::Cell>> board_;
};

} // namespace map
