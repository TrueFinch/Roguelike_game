//
// Created by truefinch on 27.05.18.
//

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Config.h"

using json = nlohmann::json;

void config::Config::loadConfig() {
  std::ifstream fin("/home/truefinch/CLionProjects/Roguelike_game/configuration/config.json");
  json json_config;
  fin >> json_config;

  for (json::iterator i = json_config.begin(); i != json_config.end(); ++i) {
    json config = *i;
    if (i.key() == "Actors") {
      for (json::iterator j = config.begin(); j != config.end(); ++j) {
        json actor_config = *j;
        if (j.key() == "Hero") {
          hero_stat_ = stats::HeroStat(actor_config["health_points_"].get<int>(),
                                       actor_config["health_points_"].get<int>(),
                                       actor_config["mana_points_"].get<int>(),
                                       actor_config["mana_points_"].get<int>(),
                                       actor_config["damage_points_"].get<int>(),
                                       actor_config["damage_points_"].get<int>(),
                                       actor_config["visibility_points_"].get<int>(),
                                       actor_config["visibility_points_"].get<int>(),
                                       actor_config["dead_symbol_code_"].get<char>(),
                                       actor_config["undead_symbol_code_"].get<char>(),
                                       actor_config["is_dead_"].get<bool>(),
                                       actor_config["is_immortal_"].get<bool>(),
                                       {0, 0});
        } else if (j.key() == "Zombie") {
          zombie_stat_ = stats::ZombieStat(actor_config["health_points_"].get<int>(),
                                           actor_config["health_points_"].get<int>(),
                                           actor_config["damage_points_"].get<int>(),
                                           actor_config["damage_points_"].get<int>(),
                                           actor_config["visibility_points_"].get<int>(),
                                           actor_config["visibility_points_"].get<int>(),
                                           actor_config["dead_symbol_code_"].get<char>(),
                                           actor_config["undead_symbol_code_"].get<char>(),
                                           actor_config["is_dead_"].get<bool>(),
                                           actor_config["is_immortal_"].get<bool>(),
                                           {0, 0});
        } else if (j.key() == "Wall") {
          wall_stat_ = stats::WallStat(actor_config["health_points_"].get<int>(),
                                       actor_config["health_points_"].get<int>(),
                                       actor_config["dead_symbol_code_"].get<char>(),
                                       actor_config["undead_symbol_code_"].get<char>(),
                                       actor_config["is_dead_"].get<bool>(),
                                       actor_config["is_immortal_"].get<bool>(),
                                       {0, 0});
        } else if (j.key() == "Princess") {
          princess_stat_ = stats::PrincessStat(actor_config["mana_points_"].get<int>(),
                                               actor_config["mana_points_"].get<int>(),
                                               actor_config["visibility_points_"].get<int>(),
                                               actor_config["visibility_points_"].get<int>(),
                                               actor_config["dead_symbol_code_"].get<char>(),
                                               actor_config["undead_symbol_code_"].get<char>(),
                                               actor_config["is_dead_"].get<bool>(),
                                               actor_config["is_immortal_"].get<bool>(),
                                               {0, 0});
        } else if (j.key() == "Dragon") {
          dragon_stat_ = stats::DragonStat(actor_config["health_points_"].get<int>(),
                                           actor_config["health_points_"].get<int>(),
                                           actor_config["mana_points_"].get<int>(),
                                           actor_config["mana_points_"].get<int>(),
                                           actor_config["damage_points_"].get<int>(),
                                           actor_config["damage_points_"].get<int>(),
                                           actor_config["visibility_points_"].get<int>(),
                                           actor_config["visibility_points_"].get<int>(),
                                           actor_config["dead_symbol_code_"].get<char>(),
                                           actor_config["undead_symbol_code_"].get<char>(),
                                           actor_config["is_dead_"].get<bool>(),
                                           actor_config["is_immortal_"].get<bool>(),
                                           {0, 0});
        }
      }
    } else if (i.key() == "Interface") {
      for (json::iterator j = config.begin(); j != config.end(); ++j) {
        json ui_config = *j;
        if (j.key() == "Loading") {
          loading_stat_ = stats::LoadingStat(ui_config["greeting_"].get<std::string>(),
                                             ui_config["hint_"].get<std::string>());
          ui_stat_.setGreeting(loading_stat_.getGreeting());
          ui_stat_.setHint(loading_stat_.getHint());
        } else if (j.key() == "MainMenu") {
          main_menu_stat_ = stats::MainMenuStat(ui_config["menu_items_"].get<std::vector<std::string>>());
          ui_stat_.setMenuItems(main_menu_stat_.getMenuItems());
        }
      }
    }
  }
}

std::shared_ptr<stats::HeroStat> config::Config::getHeroStat() const {
  return std::make_shared<stats::HeroStat>(hero_stat_);
}

std::shared_ptr<stats::ZombieStat> config::Config::getZombieStat() const {
  return std::make_shared<stats::ZombieStat>(zombie_stat_);
}

std::shared_ptr<stats::WallStat> config::Config::getWallStat() const {
  return std::make_shared<stats::WallStat>(wall_stat_);
}

std::shared_ptr<stats::PrincessStat> config::Config::getPrincessStat() const {
  return std::make_shared<stats::PrincessStat>(princess_stat_);
}

std::shared_ptr<stats::DragonStat> config::Config::getDragonStat() const {
  return std::make_shared<stats::DragonStat>(dragon_stat_);
}

std::shared_ptr<stats::UIStat> config::Config::getUIStat() const {
  return std::make_shared<stats::UIStat>(ui_stat_);
}
