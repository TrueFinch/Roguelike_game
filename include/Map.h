//
// Created by truefinch on 21.05.18.
//

#ifndef ROGUELIKE_MAP_H
#define ROGUELIKE_MAP_H

#include <Actors.h>
#include <vector>
#include <cstring>

namespace map {

class Cell {
 public:
  Cell() = default;
  Cell(actors::Point coord, actors::Actor& ref = void);
  void setReference(actors::Actor&);
  actors::Actor& getReference() const;
};

class Map {
 public:
  Map() = default;
  Map(std::vector<actors::Actor&> actors, int rows, int cols, actors::Point player_spawn);
  void move(const actors::Point& from, const actors::Point& to);
  std::vector<std::string> getArea(const actors::Point& coord, const int radius) const;
  actors::Actor& getActor(const actors::Point&) const;
 private:
//  std::vector<actors::Actor&> actors_;
  std::vector<std::vector<Cell>> board_;
  actors::Point player_spawn_;
};

} // namespace map

#endif //ROGUELIKE_MAP_H