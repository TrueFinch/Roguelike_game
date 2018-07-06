//
// Created by truefinch on 21.05.18.
//

#include <Map.h>
#include <utility>
#include <fstream>

map::Cell::Cell(std::shared_ptr<actor::Actor> ptr) : ptr_{std::move(ptr)} {}

void map::Cell::setPointer(std::shared_ptr<actor::Actor> ptr) {
  ptr_ = std::move(ptr);
}

std::shared_ptr<actor::Actor> map::Cell::getPointer() const {
  return ptr_;
}

//map::Map::Map() {}

void map::Map::loadMap(config::Config& config) {
  std::ifstream fin("/home/truefinch/CLionProjects/Roguelike_game/map/level1.txt");
  int rows = 0, cols = 0;
  std::shared_ptr<actor::Actor> actor_ptr;

  fin >> rows >> cols;
  std::string str;
  for (int i = 0; i < rows; ++i) {
    fin >> str;
    board_.emplace_back(std::vector<map::Cell>());
    for (int j = 0; j < cols; ++j) {
      auto actor_id = (enums::ActorID) str[j];
      actor_ptr = actor::Actor::createActor(actor_id, config, {(double)i, (double)j});
      board_[board_.size() - 1].emplace_back(map::Cell(actor_ptr));
    }
  }

  fin.close();
}

