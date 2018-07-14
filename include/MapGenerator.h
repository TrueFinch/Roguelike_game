//
// Created by truefinch on 13.07.18.
//
#pragma once

#include <vector>
#include <queue>
#include <Point.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

class MapGenerator {
 public:
  static MapGenerator& Instance();

  void setSize(int rows, int cols);
  void initCanvas();
  void fillCanvas();
  void readTiles();
  void addActors();
  void saveMap(const std::string&);
  bool checkReach(const Point& a, const Point& b);

  std::vector<std::vector<int>>& getCanvas() const;
  std::vector<std::string>& getMap() const;

 private:
  MapGenerator() = default;
  ~MapGenerator() = default;

  MapGenerator(MapGenerator const&) = delete;
  MapGenerator& operator=(MapGenerator const&) = delete;

  std::vector<std::vector<int>> canvas_;
  std::vector<std::string> map_;
  std::vector<std::vector<std::string>> tiles_;
  int canvas_rows_ = 0, canvas_cols_ = 0, map_rows_ = 0, map_cols_ = 0, tile_rows_ = 0, tile_cols_ = 0;
};