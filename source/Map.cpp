//
// Created by truefinch on 21.05.18.
//

#include <Map.h>
#include <utility>

map::Cell::Cell(actors::Point coord, std::shared_ptr<actors::Actor> ptr = nullptr) : coord_{coord},
                                                                                     ptr_{std::move(ptr)} {}

void map::Cell::setPointer(std::shared_ptr<actors::Actor> ptr) {
  ptr_ = std::move(ptr);
}

std::shared_ptr<actors::Actor> map::Cell::getPointer() const {
  return ptr_;
}

void map::Map::loadMap() {
  FILE* map = fopen("./map/level1.txt", "rt");
  int rows = 0, cols = 0;
  char c;
  std::shared_ptr<actors::Actor> actor_ptr;
  fscanf(map, "%i\n%i\n", &rows, &cols);

  for (int i = 0; i < rows; ++i) {
    std::vector<Cell> tmp((unsigned long) (cols));
    for (int j = 0; i < cols; ++j) {
      fscanf(map, "%c", &c);
      switch (c) {
        case '@':
          actor_ptr = actors::Actor::createActor(actors::HERO_ID, {{'D', 100},
                                                                   {'M', 100},
                                                                   {'H', 100},
                                                                   {'R', i},
                                                                   {'C', j}});
          break;
        case 'z':
          actor_ptr = actors::Actor::createActor(actors::ZOMBIE_ID, {{'D', 100},
                                                                     {'H', 100},
                                                                     {'R', i},
                                                                     {'C', j}});
          break;
        case '#':
          actor_ptr = actors::Actor::createActor(actors::WALL_ID, {{'H', 100},
                                                                   {'R', i},
                                                                   {'C', j}});
          break;
        case '.':
          actor_ptr = nullptr;
          break;
      }
      if (actor_ptr != nullptr) {
        actors_.push_back(actor_ptr);
      }
      tmp.emplace_back({{i, j}, actor_ptr});
    }
    board_.push_back(tmp);
    fscanf(map, "\n");
  }
}