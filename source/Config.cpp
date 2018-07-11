//
// Created by truefinch on 27.05.18.
//

#include "Config.h"
#include <string>
#include <fstream>

config::Config& config::Config::Instance() {
  static Config self;
  return self;
}

void config::Config::init_actors(const std::string& path) {
  std::ifstream fin("/home/truefinch/CLionProjects/Roguelike_game/configuration/config_level_1.json");
  json json_config;
  fin >> json_config;
  for (json::iterator i = json_config.begin(); i != json_config.end(); ++i) {
    json config = *i;
    if (i.key() == "Default_actors") {
      for (json::iterator j = config.begin(); j != config.end(); ++j) {
        json actor_config = *j;
        if (j.key() == "Hero") {
          hero_ = actor_config;
        } else if (j.key() == "Zombie") {
          zombie_ = actor_config;
        } else if (j.key() == "Dragon") {
          dragon_ = actor_config;
        } else if (j.key() == "Princess") {
          princess_ = actor_config;
        } else if (j.key() == "Fireball") {
          fireball_ = actor_config;
        } else if (j.key() == "Wall") {
          wall_ = actor_config;
        } else if (j.key() == "Floor") {
          floor_ = actor_config;
        } else if (j.key() == "HealthPotion") {
          health_potion_ = actor_config;
        } else if (j.key() == "ManaPotion") {
          mana_potion_ = actor_config;
        }
      }
    }
  }
  fin.close();
}

json config::Config::getHero() const {
  return hero_;
}

json config::Config::getZombie() const {
  return zombie_;
}

json config::Config::getDragon() const {
  return dragon_;
}

json config::Config::getPrincess() const {
  return princess_;
}

json config::Config::getFireball() const {
  return fireball_;
}

json config::Config::getWall() const {
  return wall_;
}

json config::Config::getFloor() const {
  return floor_;
}

json config::Config::getHealthPotion() const {
  return health_potion_;
}

json config::Config::getManaPotion() const {
  return mana_potion_;
}

void config::Config::init_ui(const std::string& path) {
  std::ifstream fin(path);
  json json_config;
  fin >> json_config;

  for (json::iterator i = json_config.begin(); i != json_config.end(); ++i) {
    json ui_config = *i;
    if (i.key() == "Loading") {
      loading_ = ui_config;
    } else if (i.key() == "MainMenu") {
      main_menu_ = ui_config;
    }
  }
}

json config::Config::getLoading() const {
  return loading_;
}

json config::Config::getMainMenu() const {
  return main_menu_;
}

