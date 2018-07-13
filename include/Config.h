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
  void initActors(const std::string& path);
  json getHero() const;
  json getZombie() const;
  json getDragon() const;
  json getPrincess() const;
  json getFireball() const;
  json getWall() const;
  json getFloor() const;
  json getHealthPotion() const;
  json getManaPotion() const;

  void initUI(const std::string& path);
  json getLoading() const;
  json getMainMenu() const;
  json getPauseMenu() const;
  json getSumUpMenu() const;

  void initGameManager(const std::string& path);
  json getGameManager() const;
 private:
  Config() = default;
  ~Config() = default;
  Config(Config const&) = delete;
  Config& operator=(Config const&) = delete;

  json hero_;
  json zombie_;
  json dragon_;
  json princess_;
  json fireball_;
  json wall_;
  json floor_;
  json health_potion_;
  json mana_potion_;

  json loading_;
  json main_menu_;
  json pause_menu_;
  json sum_up_menu_;

  json game_manager_;
};

} // namespace config
