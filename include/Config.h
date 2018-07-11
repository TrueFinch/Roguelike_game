//
// Created by truefinch on 27.05.18.
//
#pragma once

#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace config {

class Config {
 public:
  static Config& Instance();
  void init(const std::string& path);
  json getHero();
  json getZombie();
  json getDragon();
  json getPrincess();
  json getFireball();
  json getWall();
  json getFloor();
  json getHealthPotion();
  json getManaPotion();

 private:
  Config() = default;
  ~Config() = default;
  Config(Config const&) = delete;
  Config& operator= (Config const&) = delete;

  json hero_;
  json zombie_;
  json dragon_;
  json princess_;
  json fireball_;
  json wall_;
  json floor_;
  json health_potion_;
  json mana_potion_;
};

} // namespace config
