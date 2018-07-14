//
// Created by truefinch on 21.05.18.
//

#pragma once

#include <vector>
#include <stack>
#include <cstring>
#include <memory>
#include <Actors.h>

namespace map {

class Cell;

class Map;

class Cell {
 public:
  Cell() = default;
  void push(std::shared_ptr<actor::Actor>);
  void pop();
  std::shared_ptr<actor::Actor> top() const;
 private:
  std::stack<std::shared_ptr<actor::Actor>> actors_;
};

class Map {
 public:
  static Map& Instance();
  void loadMap(std::vector<enums::ActorID>&, std::vector<Point>&, const std::string&);
  std::vector<std::vector<std::shared_ptr<actor::Actor>>> getArea(const Point& coord, int radius) const;
  std::shared_ptr<std::vector<std::string>> getMapView() const;
  void addActorToCell(std::shared_ptr<actor::Actor>, const Point&);
  void move(Point a, Point b);
  bool loaded = false;
 private:
  int rows_, cols_;
  Map() = default;
  ~Map() = default;

  Map(Map const&) = delete;
  Map& operator=(Map const&) = delete;
  std::vector<std::vector<map::Cell>> board_;
};

} // namespace map
