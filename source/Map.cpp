//
// Created by truefinch on 21.05.18.
//

#include <Map.h>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <cmath>

void map::Cell::push(std::shared_ptr<actor::Actor> actor) {
  this->actors_.push(actor);
}

void map::Cell::pop() {
  this->actors_.pop();
}

std::shared_ptr<actor::Actor> map::Cell::top() const {
  return this->actors_.top();
}

map::Map& map::Map::Instance() {
  static Map self;
  return self;
}

std::shared_ptr<std::vector<std::string>> map::Map::getMapView() const {
  //TODO: add fog of war
  std::vector<std::string> map_view;
  for (const auto& row : this->board_) {
    map_view.emplace_back(std::string());
    for (const auto& cell : row) {
      char c = (cell.top()->isDead()) ? (cell.top()->getDeadSymbol()) : (cell.top()->getLiveSymbol());
      map_view[map_view.size() - 1].push_back(c);
    }
  }
  return std::make_shared<std::vector<std::string>>(map_view);
}

std::vector<std::vector<std::shared_ptr<actor::Actor>>> map::Map::getArea(const Point& coord, const int radius) const {
  std::vector<std::vector<std::shared_ptr<actor::Actor>>> area;

  int row = (int) coord.x, col = (int) coord.y,
      top_row_bound = row - std::min<int>(radius, row),
      bottom_row_bound = row + std::min<int>(radius, map::Map::Instance().rows_ - row - 1),
      left_row_bound = col - std::min<int>(radius, col),
      right_col_bound = col + std::min<int>(radius, map::Map::Instance().cols_ - col - 1);

  for (int i = top_row_bound; i <= bottom_row_bound; ++i) {
    area.emplace_back(std::vector<std::shared_ptr<actor::Actor>>());
    for (int j = left_row_bound; j <= right_col_bound; ++j) {
      area[area.size() - 1].push_back(board_[i][j].top());
    }
  }
  return area;
}

void map::Map::loadMap(std::vector<enums::ActorID>& actors, std::vector<Point>& positions, const std::string& path) {
  std::ifstream fin(path);
  fin >> rows_ >> cols_;
  map::Map::Instance().rows_ = rows_;
  map::Map::Instance().cols_ = cols_;
  std::string str;
  for (int i = 0; i < rows_; ++i) {
    fin >> str;
    board_.emplace_back(std::vector<map::Cell>(static_cast<unsigned long>(cols_)));
    for (int j = 0; j < cols_; ++j) {
      auto actor_id = enums::FLOOR_ID;
      actors.push_back(actor_id);
      positions.emplace_back(i, j);
      actor_id = (enums::ActorID) str[j];
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

void map::Map::move(Point a, Point b) {
  std::shared_ptr<actor::Actor> moved = this->board_[a.x][a.y].top();
  this->board_[a.x][a.y].pop();
  this->board_[b.x][b.y].push(moved);

  this->board_[b.x][b.y].top()->setPosition({b.x, b.y});
}


