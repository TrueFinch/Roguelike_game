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

void config::Config::init(const std::string& path) {
  std::ifstream fin("/home/truefinch/CLionProjects/Roguelike_game/configuration/config_level1.json");
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

json config::Config::getHero()  {
  return hero_;
}

json config::Config::getZombie() {
  return zombie_;
}

json config::Config::getDragon() {
  return dragon_;
}

json config::Config::getPrincess() {
  return princess_;
}

json config::Config::getFireball() {
  return fireball_;
}

json config::Config::getWall() {
  return wall_;
}

json config::Config::getFloor() {
  return floor_;
}

json config::Config::getHealthPotion() {
  return health_potion_;
}

json config::Config::getManaPotion() {
  return mana_potion_;
}

