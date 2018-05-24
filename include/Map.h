//
// Created by truefinch on 21.05.18.
//

#ifndef ROGUELIKE_MAP_H
#define ROGUELIKE_MAP_H

#include <Actors.h>
#include <vector>
#include <cstring>
#include <memory>

namespace map {

class Cell {
 public:
  Cell() = default;
  Cell(actors::Point coord, std::shared_ptr<actors::Actor> ptr = nullptr);
  void setPointer(std::shared_ptr<actors::Actor>);
  std::shared_ptr<actors::Actor> getPointer() const;
 private:
  actors::Point coord_;
  std::shared_ptr<actors::Actor> ptr_;
};

class Map {
 public:
  Map() = default;
  void loadMap();
  std::vector<std::string> getArea(const actors::Point& coord, const int radius) const;
 private:
  std::vector<std::shared_ptr<actors::Actor>> actors_;
  std::vector<std::vector<Cell>> board_;
};

} // namespace map

#endif //ROGUELIKE_MAP_H