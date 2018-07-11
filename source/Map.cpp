//
// Created by truefinch on 21.05.18.
//

#include <Map.h>
#include <utility>
#include <fstream>
#include <cassert>

void map::Cell::push(std::shared_ptr<actor::Actor> actor) {
  this->actors_.push(actor);
}

void map::Cell::pop() {
  this->actors_.pop();
}
std::shared_ptr<actor::Actor> map::Cell::top () const {
  return this->actors_.top();
}

map::Map& map::Map::Instance() {
  static Map self;
  return self;
}

std::shared_ptr<std::vector<std::string>> map::Map::getMapView() const {
  std::vector<std::string> map_view;
  for (const auto& row : this->board_) {
    map_view.emplace_back(std::string());
    for (const auto& cell : row) {
      char c;
     map_view[map_view.size() - 1].push_back(cell.top()->getLiveSymbol());
//      switch ((cell.getPointer() == nullptr) ? (enums::NOTHING_ID) : (cell.getPointer()->sayID())) {
//        case enums::ActorID::HERO_ID:
//          c = std::dynamic_pointer_cast<actor::Hero>(cell.getPointer())->getUndeadSymbol();
//          break;
//        case enums::ActorID::ZOMBIE_ID:
//          c = std::dynamic_pointer_cast<actor::Zombie>(cell.getPointer())->getUndeadSymbol();
//          break;
//        case enums::ActorID::WALL_ID:
//          c = std::dynamic_pointer_cast<actor::Wall>(cell.getPointer())->getUndeadSymbol();
//          break;
//        case enums::ActorID::PRINCESS_ID:
//          c = std::dynamic_pointer_cast<actor::Princess>(cell.getPointer())->getUndeadSymbol();
//          break;
//        case enums::ActorID::DRAGON_ID:
//          c = std::dynamic_pointer_cast<actor::Dragon>(cell.getPointer())->getUndeadSymbol();
//          break;
//        case enums::ActorID::NOTHING_ID:
//          c = '.';
//          break;
//        default:
//          assert(false);
//      }
      map_view[map_view.size() - 1].push_back(c);
    }
  }
  return std::make_shared<std::vector<std::string>>(map_view);
}

std::vector<std::vector<std::shared_ptr<actor::Actor>>> map::Map::getArea(const Point& coord, const int radius) const {
  std::vector<std::vector<std::shared_ptr<actor::Actor>>> area;
  for (int i = 0; i < (2 * radius); ++i) {
    area.emplace_back(std::vector<std::shared_ptr<actor::Actor>>());
    for (int j = 0; j < (2 * radius); ++j) {
      area[area.size() - 1].push_back(board_[coord.x - radius + i][coord.y - radius + j].top());
      area[area.size() - 1].push_back(board_[coord.x - radius + i][coord.y - radius + j].top());
    }
  }
  return area;
}

void map::Map::loadMap(std::vector<enums::ActorID>& actors, std::vector<Point>& positions, const std::string& path) {
  std::ifstream fin(path);
  int rows, cols;
  fin >> rows >> cols;
  std::string str;
  for (int i = 0; i < rows; ++i) {
    fin >> str;
    board_.emplace_back(std::vector<map::Cell>(static_cast<unsigned long>(cols)));
    for (int j = 0; j < cols; ++j) {
      auto actor_id = (enums::ActorID) str[j];
      actors.push_back(actor_id);
      positions.emplace_back(i, j);
    }
  }
  loaded = true;
  fin.close();
}

void map::Map::addActorToCell(std::shared_ptr<actor::Actor> actor_ptr, const Point& position) {
  board_[position.x][position.y].push(std::move(actor_ptr));
}

void map::Map::swap(Point a, Point b) {
  std::shared_ptr<actor::Actor> tmp = this->board_[a.x][a.y].top();
  this->board_[a.x][a.y].pop();
  this->board_[a.x][a.y].push(this->board_[b.x][b.y].top());
  this->board_[b.x][b.y].pop();
  this->board_[b.x][b.y].push(tmp);
}


