//
// Created by truefinch on 21.05.18.
//

#include <Map.h>
#include <utility>
#include <fstream>
#include <cassert>

map::Cell::Cell(std::shared_ptr<actor::Actor> ptr) : ptr_{std::move(ptr)} {}

void map::Cell::setPointer(std::shared_ptr<actor::Actor> ptr) {
  ptr_ = std::move(ptr);
}

std::shared_ptr<actor::Actor> map::Cell::getPointer() const {
  return ptr_;
}

//map::Map::Map() {}

std::shared_ptr<actor::Hero> map::Map::loadMap(std::vector<std::shared_ptr<actor::Actor>>& npc,
                       config::Config& config) {
  std::shared_ptr<actor::Hero> hero_ptr;
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
      actor_ptr = actor::Actor::createActor(actor_id, config, {(double) i, (double) j});
      if ((actor_id == enums::ZOMBIE_ID) or (actor_id == enums::DRAGON_ID) or actor_id == enums::FIRE_BALL_ID) {
        npc.push_back(actor_ptr);
      } else if (actor_id == enums::HERO_ID) {
        hero_ptr = std::static_pointer_cast<actor::Hero>(actor_ptr);
      }
      board_[board_.size() - 1].emplace_back(map::Cell(actor_ptr));
    }
  }

  fin.close();
  return hero_ptr;
}

std::shared_ptr<std::vector<std::string>> map::Map::getMapView() const {
  std::vector<std::string> map_view;
  for (const auto& row : this->board_) {
    map_view.emplace_back(std::string());
    for (const auto& cell : row) {
      char c;
      switch ((cell.getPointer() == nullptr) ? (enums::NOTHING_ID) : (cell.getPointer()->sayID())) {
        case enums::ActorID::HERO_ID:
          c = std::dynamic_pointer_cast<actor::Hero>(cell.getPointer())->getUndeadSymbol();
          break;
        case enums::ActorID::ZOMBIE_ID:
          c = std::dynamic_pointer_cast<actor::Zombie>(cell.getPointer())->getUndeadSymbol();
          break;
        case enums::ActorID::WALL_ID:
          c = std::dynamic_pointer_cast<actor::Wall>(cell.getPointer())->getUndeadSymbol();
          break;
        case enums::ActorID::PRINCESS_ID:
          c = std::dynamic_pointer_cast<actor::Princess>(cell.getPointer())->getUndeadSymbol();
          break;
        case enums::ActorID::DRAGON_ID:
          c = std::dynamic_pointer_cast<actor::Dragon>(cell.getPointer())->getUndeadSymbol();
          break;
        case enums::ActorID::NOTHING_ID:
          c = '.';
          break;
        default:
          assert(false);
      }
      map_view[map_view.size() - 1].push_back(c);
    }
  }
  return std::make_shared<std::vector<std::string>>(map_view);
}

