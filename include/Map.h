//
// Created by truefinch on 21.05.18.
//

#ifndef ROGUELIKE_MAP_H
#define ROGUELIKE_MAP_H

#include <Actors.h>

namespace map {

class Cell {
 public:
  Cell() = default;
  Cell(actors::Point coord, actors::Actor& ref = void);
  void setReference(actors::Actor&);
  actors::Actor& getReference() const;
};

} // namespace map

#endif //ROGUELIKE_MAP_H
