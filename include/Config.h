//
// Created by truefinch on 27.05.18.
//
#pragma once

#include <Statistics.h>
#include <memory>

namespace config {

class Config {
 public:
  Config() = default;
  void loadConfig();
  std::shared_ptr<stats::HeroStat> getHeroStat() const;
  std::shared_ptr<stats::ZombieStat> getZombieStat() const;
  std::shared_ptr<stats::WallStat> getWallStat() const;
  std::shared_ptr<stats::PrincessStat> getPrincessStat() const;
  std::shared_ptr<stats::DragonStat> getDragonStat() const;
  std::shared_ptr<stats::UIStat> getUIStat() const;
 private:
  stats::HeroStat hero_stat_;
  stats::PrincessStat princess_stat_;
  stats::ZombieStat zombie_stat_;
  stats::DragonStat dragon_stat_;
  stats::WallStat wall_stat_;
  stats::LoadingStat loading_stat_;
  stats::MainMenuStat main_menu_stat_;
  stats::UIStat ui_stat_;
};

} // namespace config
