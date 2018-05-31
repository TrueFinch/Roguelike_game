//
// Created by truefinch on 27.05.18.
//

#include <fstream>
#include <nlohmann/json.hpp>
#include "Config.h"

using json = nlohmann::json;

void config::Config::loadConfig() {
  std::ifstream fin("/home/truefinch/CLionProjects/Roguelike_game/configuration/config.json");
  json json_config;
  fin >> json_config;
  for (json::iterator i = json_config.begin(); i != json_config.end(); ++i) {
    if (i.key() == "Actors") {
      json actors_config = *i;
      for (json::iterator j = actors_config.begin(); j != actors_config.end(); ++j) {
        if (j.key() == "Hero") {
          json hero_config = *j;
          hero_stat_ = stats::HeroStat(hero_config["max_health_points_"].get<int>(),
                                       hero_config["max_health_points_"].get<int>(),
                                       hero_config["max_mana_points_"].get<int>(),
                                       hero_config["max_mana_points_"].get<int>(),
                                       hero_config["damage_points_"].get<int>(),
                                       hero_config["damage_points_"].get<int>(),
                                       hero_config["visibility_points_"].get<int>(),
                                       hero_config["visibility_points_"].get<int>(),
                                       hero_config["undead_symbol_"].get<char>(),
                                       hero_config["dead_symbol_"].get<char>(),
                                       hero_config["is_dead_"].get<bool>(),
                                       hero_config["is_immortal_"].get<bool>(),
                                       {0, 0});
          continue;
        }
        if (j.key() == "Zombie") {
          json zombie_config = *j;
          zombie_stat_ = stats::ZombieStat(zombie_config["max_health_points_"].get<int>(),
                                           zombie_config["max_health_points_"].get<int>(),
                                           zombie_config["damage_points_"].get<int>(),
                                           zombie_config["damage_points_"].get<int>(),
                                           zombie_config["visibility_points_"].get<int>(),
                                           zombie_config["visibility_points_"].get<int>(),
                                           zombie_config["undead_symbol_"].get<char>(),
                                           zombie_config["dead_symbol_"].get<char>(),
                                           zombie_config["is_dead_"].get<bool>(),
                                           zombie_config["is_immortal_"].get<bool>(),
                                           {0, 0});
          continue;
        }
        if (j.key() == "Wall") {
          json wall_config = *j;
          wall_stat_ = stats::WallStat(wall_config["max_health_points_"].get<int>(),
                                       wall_config["max_health_points_"].get<int>(),
                                       wall_config["undead_symbol_"].get<char>(),
                                       wall_config["dead_symbol_"].get<char>(),
                                       wall_config["is_dead_"].get<bool>(),
                                       wall_config["is_immortal_"].get<bool>(),
                                       {0, 0});
          continue;
        }
        if (j.key() == "Princess") {
          json princess_config = *j;
          princess_stat_ = stats::PrincessStat(princess_config["max_mana_points_"].get<int>(),
                                               princess_config["max_mana_points_"].get<int>(),
                                               princess_config["visibility_points_"].get<int>(),
                                               princess_config["visibility_points_"].get<int>(),
                                               princess_config["undead_symbol_"].get<char>(),
                                               princess_config["dead_symbol_"].get<char>(),
                                               princess_config["is_dead_"].get<bool>(),
                                               princess_config["is_immortal_"].get<bool>(),
                                               {0, 0});
          continue;
        }
        if (j.key() == "Dragon") {
          json dragon_config = *j;
          dragon_stat_ = stats::DragonStat(dragon_config["max_health_points_"].get<int>(),
                                         dragon_config["max_health_points_"].get<int>(),
                                         dragon_config["max_mana_points_"].get<int>(),
                                         dragon_config["max_mana_points_"].get<int>(),
                                         dragon_config["damage_points_"].get<int>(),
                                         dragon_config["damage_points_"].get<int>(),
                                         dragon_config["visibility_points_"].get<int>(),
                                         dragon_config["visibility_points_"].get<int>(),
                                         dragon_config["undead_symbol_"].get<char>(),
                                         dragon_config["dead_symbol_"].get<char>(),
                                         dragon_config["is_dead_"].get<bool>(),
                                         dragon_config["is_immortal_"].get<bool>(),
                                         {0, 0});
          continue;
        }
      }
    }
  }
}

const stats::HeroStat& config::Config::getHeroStat() const {
  return hero_stat_;
}

const stats::ZombieStat& config::Config::getZombieStat() const {
  return zombie_stat_;
}

const stats::WallStat& config::Config::getWallStat() const {
  return wall_stat_;
}

const stats::PrincessStat& config::Config::getPrincessStat() const {
  return princess_stat_;
}

const stats::DragonStat& config::Config::getDragonStat() const {
  return dragon_stat_;
}
