//
// Created by truefinch on 13.07.18.
//

#include <random>
#include "MapGenerator.h"

MapGenerator& MapGenerator::Instance() {
  static MapGenerator self;
  return self;
}

void MapGenerator::setSize(const int rows, const int cols) {
  MapGenerator& gen = MapGenerator::Instance();

  gen.canvas_.resize((unsigned long) rows);
  for (auto& row: gen.canvas_) {
    row.resize((unsigned long) cols);
  }
  gen.canvas_rows_ = rows;
  gen.canvas_cols_ = cols;
}

void MapGenerator::initCanvas() {
  //TODO: add check if tiles are uploaded
  MapGenerator& mapGenerator = MapGenerator::Instance();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 7);

  for (int i = 0; i < mapGenerator.canvas_rows_; ++i) {
    for (int j = 0; j < mapGenerator.canvas_cols_; ++j) {
      mapGenerator.canvas_[i][j] = 0;
    }
  }
  for (int i = 1; i < mapGenerator.canvas_rows_ - 1; ++i) {
    for (int j = 1; j < mapGenerator.canvas_cols_ - 1; ++j) {
      int a = dis(gen);
      while ((a == mapGenerator.canvas_[i][j - 1]) or (a == mapGenerator.canvas_[i - 1][j])) {
        a = dis(gen);
      }
      mapGenerator.canvas_[i][j] = a;
    }
  }

}

std::vector<std::vector<int>>& MapGenerator::getCanvas() const {
  return MapGenerator::Instance().canvas_;
}

void MapGenerator::fillCanvas() {
  MapGenerator& mapGenerator = MapGenerator::Instance();

  //TODO: replace init of map like it did in checkReach
  mapGenerator.map_rows_ = mapGenerator.canvas_rows_ * tile_rows_;
  mapGenerator.map_cols_ = mapGenerator.canvas_cols_ * tile_cols_;

  mapGenerator.map_.resize((unsigned long) mapGenerator.canvas_rows_ * 5);
  for (auto& row: mapGenerator.map_) {
    row.resize((unsigned long) mapGenerator.canvas_cols_ * 5);
  }
  for (int k = 0; k < mapGenerator.canvas_rows_; ++k)
    for (int h = 0; h < mapGenerator.canvas_cols_; ++h)
      for (int i = 0; i < mapGenerator.tile_rows_; ++i)
        for (int j = 0; j < mapGenerator.tile_cols_; ++j)
          mapGenerator.map_[i + 5 * k][j + 5 * h] = mapGenerator.tiles_[mapGenerator.canvas_[k][h]][i % 5][j % 5];

}

void MapGenerator::readTiles() {
  MapGenerator& mapGenerator = MapGenerator::Instance();

  //TODO: remove to initMapGenerator
  mapGenerator.tile_rows_ = 5;
  mapGenerator.tile_cols_ = 5;

  std::ifstream tile_file;
  for (int i = 0; i < 8; ++i) {
    tile_file.open("/home/truefinch/CLionProjects/Roguelike_game/map/map_templates/tile_" + std::to_string(i));
    mapGenerator.tiles_.emplace_back(std::vector<std::string>());
    for (int j = 0; j < 5; ++j) {
      std::string str;
      tile_file >> str;
      mapGenerator.tiles_[mapGenerator.tiles_.size() - 1].push_back(str);
    }
    tile_file.close();
  }
  tile_file.close();
}

std::vector<std::string>& MapGenerator::getMap() const {
  return MapGenerator::Instance().map_;
}

void MapGenerator::addActors() {
  MapGenerator& mapGenerator = MapGenerator::Instance();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_x(0, mapGenerator.map_rows_ - 2 * mapGenerator.tile_rows_ - 1);
  std::uniform_int_distribution<> dis_y(0, mapGenerator.map_cols_ - 2 * mapGenerator.tile_cols_ - 1);
  //TODO: create an const var that handle the max random number
  std::uniform_int_distribution<> dis(0, 100);

  Point hero_pos, princess_pos;

  do {
    hero_pos = {dis_x(gen) + mapGenerator.tile_rows_, dis_y(gen) + mapGenerator.tile_cols_};
    princess_pos = {dis_x(gen) + mapGenerator.tile_rows_, dis_y(gen) + mapGenerator.tile_cols_};
  } while (!checkReach(hero_pos, princess_pos));

  mapGenerator.map_[hero_pos.x][hero_pos.y] = '@';
  mapGenerator.map_[princess_pos.x][princess_pos.y] = 'P';

  //TODO: compress all those cycles to only one (use a cycle by the array of actor symbols
  std::vector<char> actors_symbols(4);
  actors_symbols[0] = 'Z';
  actors_symbols[1] = 'D';
  actors_symbols[2] = 'H';
  actors_symbols[3] = 'M';
  for (int i = 0; i < 4; ++i) {
    //TODO: remove the % 25 + 25 to mapGenerator configuration file
    int generated = 0, amount = dis(gen) % 25 + 25;
    if (i == 1) {
      amount = dis(gen) % 2 + 3;
    }
    for (Point pos = {dis_x(gen) + mapGenerator.tile_rows_, dis_y(gen) + mapGenerator.tile_cols_}; generated < amount;
         pos = {dis_x(gen) + mapGenerator.tile_rows_, dis_y(gen) + mapGenerator.tile_cols_}) {
      if (mapGenerator.map_[pos.x][pos.y] == '.') {
        mapGenerator.map_[pos.x][pos.y] = actors_symbols[i];
      }
      ++generated;
    }
  }
}

bool MapGenerator::checkReach(const Point& a, const Point& b) {
  MapGenerator& mapGenerator = MapGenerator::Instance();

  if ((mapGenerator.map_[a.x][a.y] == '#') or (mapGenerator.map_[b.x][b.y] == '#')) {
    return false;
  }

  std::vector<std::vector<bool>>
      visited(mapGenerator.map_rows_, std::vector<bool>(mapGenerator.map_cols_, false));
  std::queue<Point> q;

  q.push(a);
  visited[a.x][a.y] = true;

  while (!q.empty()) {
    Point p = q.front();
    visited[p.x][p.y] = true;
    q.pop();
    if ((mapGenerator.map_[p.x - 1][p.y] == '.') and (!visited[p.x - 1][p.y])) {
      if (mapGenerator.map_[p.x - 1][p.y] == mapGenerator.map_[b.x][b.y]) {
        visited[b.x][b.y] = true;
        break;
      }
      q.push({p.x - 1, p.y});
    }
    if ((mapGenerator.map_[p.x + 1][p.y] == '.') and (!visited[p.x + 1][p.y])) {
      if (mapGenerator.map_[p.x + 1][p.y] == mapGenerator.map_[b.x][b.y]) {
        visited[b.x][b.y] = true;
        break;
      }
      q.push({p.x + 1, p.y});
    }
    if ((mapGenerator.map_[p.x][p.y - 1] == '.') and (!visited[p.x][p.y - 1])) {
      if (mapGenerator.map_[p.x][p.y - 1] == mapGenerator.map_[b.x][b.y]) {
        visited[b.x][b.y] = true;
        break;
      }
      q.push({p.x, p.y - 1});
    }
    if ((mapGenerator.map_[p.x][p.y + 1] == '.') and (!visited[p.x][p.y + 1])) {
      if (mapGenerator.map_[p.x][p.y + 1] == mapGenerator.map_[b.x][b.y]) {
        visited[b.x][b.y] = true;
        break;
      }
      q.push({p.x, p.y + 1});
    }
  }
  return (visited[a.x][a.y]) and (visited[b.x][b.y]);
}

void MapGenerator::saveMap() {
  MapGenerator& mapGenerator = MapGenerator::Instance();

  std::ofstream map_file;
  map_file.open("/home/truefinch/CLionProjects/Roguelike_game/map/level");
  map_file << mapGenerator.map_rows_ << std::endl << mapGenerator.map_cols_ << std::endl;
  for (int i = 0; i < mapGenerator.map_rows_; ++i) {
    map_file << mapGenerator.map_[i] << std::endl;
  }
  map_file.close();
}

