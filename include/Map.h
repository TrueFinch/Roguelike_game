//
// Created by truefinch on 21.05.18.
//

#pragma once

#include <vector>
#include <stack>
#include <cstring>
#include <memory>
#include <Config.h>
#include <Actors.h>


namespace map {

class Cell;

class Map;

class Cell {
 public:
  Cell() = default;
  void push(std::shared_ptr<actor::Actor>);
  void pop();
  std::shared_ptr<actor::Actor> top () const;
 private:
  std::stack<std::shared_ptr<actor::Actor>> actors_;
};

class Map {
 public:
  static Map& Instance();
//  std::shared_ptr<actor::Hero> loadMap(std::vector<std::shared_ptr<actor::Actor>>& actors, config::Config&);
  std::vector<std::vector<std::shared_ptr<actor::Actor>>> getArea(const Point& coord, int radius) const;
  std::shared_ptr<std::vector<std::string>> getMapView() const;
 private:
  Map() = default;
  ~Map() = default;

  Map(Map const&) = delete;
  Map& operator= (Map const&) = delete;
  std::vector<std::vector<map::Cell>> board_;
};

} // namespace map
