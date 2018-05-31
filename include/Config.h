//
// Created by truefinch on 27.05.18.
//

#ifndef ROGUELIKE_CONFIG_H
#define ROGUELIKE_CONFIG_H

#include <Statistics.h>

namespace config {

class Config {
 public:
  Config() = default;
  void loadConfig();
  const stats::HeroStat& getHeroStat() const;
  const stats::ZombieStat& getZombieStat() const;
  const stats::WallStat& getWallStat() const;
  const stats::PrincessStat& getPrincessStat() const;
  const stats::DragonStat& getDragonStat() const;
 private:
  stats::HeroStat hero_stat_;
  stats::PrincessStat princess_stat_;
  stats::ZombieStat zombie_stat_;
  stats::DragonStat dragon_stat_;
  stats::WallStat wall_stat_;
};

} // namespace config
#endif //ROGUELIKE_CONFIG_H
