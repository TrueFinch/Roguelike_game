//
// Created by truefinch on 27.05.18.
//
#pragma once

#include <Point.h>
#include <string>
#include <vector>

namespace stats {

class Statistics {
 public:
  Statistics() = default;
  virtual ~Statistics() = default;
};

//health points statistics
class HPStat {
 public:
  HPStat() = default;
  HPStat(int max, int cur);
  void setMaxHP(int);
  int getMaxHP() const;
  void setCurHP(int);
  int getCurHP() const;
 protected:
  int max_health_points_ = 0;
  int cur_health_points_ = 0;
};

//mana points statistics
class MPStat {
 public:
  MPStat() = default;
  MPStat(int max, int cur);
  void setMaxMP(int);
  int getMaxMP() const;
  void setCurMP(int);
  int getCurMP() const;
 protected:
  int max_mana_points_ = 0;
  int cur_mana_points_ = 0;
};

//damage points statistics
class DPStat {
 public:
  DPStat() = default;
  DPStat(int, int);
  void setMaxDP(int);
  int getMaxDP() const;
  void setCurDP(int);
  int getCurDP() const;
 protected:
  int max_damage_points_ = 0;
  int cur_damage_points_ = 0;
};

//visibility points statistics
class VPStat {
 public:
  VPStat() = default;
  VPStat(int, int);
  void setMaxVP(int);
  int getMaxVP() const;
  void setCurVP(int);
  int getCurVP() const;
 protected:
  int max_visibility_points_ = 0;
  int cur_visibility_points_ = 0;
};

//is actor dead or immortal statistics
class SpecialFlagsStat {
 public:
  SpecialFlagsStat() = default;
  SpecialFlagsStat(bool, bool);
  void setDead(bool);
  bool isDead() const;
  void setImmortal(bool);
  bool isImmortal() const;
 protected:
  bool is_dead_ = false;
  bool is_immortal_ = false;
};

//statistics of actor's symbol
class SymbolsStat {
 public:
  SymbolsStat() = default;
  SymbolsStat(char, char);
  void setDeadSymbol(char);
  char getDeadSymbol() const;
  void setUndeadSymbol(char);
  char getUndeadSymbol() const;
 protected:
  char dead_symbol_ = '4';
  char undead_symbol_ = '2';
};

//actor's coordinate statistics
class CoordinateStat {
 public:
  CoordinateStat() = default;
  explicit CoordinateStat(Point);
  CoordinateStat(double, double);
  void setCoord(Point p);
  Point getCoord() const;
 protected:
  Point coordinate_ = {42, 42};
};

class HeroStat : public Statistics,
                 public HPStat,
                 public MPStat,
                 public DPStat,
                 public VPStat,
                 public SymbolsStat,
                 public SpecialFlagsStat,
                 public CoordinateStat {
 public:
  HeroStat() = default;
  HeroStat(int max_hp,
           int cur_hp,
           int max_mp,
           int cur_mp,
           int max_dp,
           int cur_dp,
           int max_vp,
           int cur_vp,
           char dead_symbol,
           char undead_symbol,
           bool is_dead,
           bool is_immortal,
           Point p);
};

class PrincessStat : public Statistics,
                     public MPStat,
                     public VPStat,
                     public SymbolsStat,
                     public SpecialFlagsStat,
                     public CoordinateStat {
 public:
  PrincessStat() = default;
  PrincessStat(int max_mp,
               int cur_mp,
               int max_vp,
               int cur_vp,
               char dead_symbol,
               char undead_symbol,
               bool is_dead,
               bool is_immortal,
               Point p);
};

class ZombieStat : public Statistics,
                   public HPStat,
                   public DPStat,
                   public VPStat,
                   public SymbolsStat,
                   public SpecialFlagsStat,
                   public CoordinateStat {
 public:
  ZombieStat() = default;
  ZombieStat(int max_hp,
             int cur_hp,
             int max_dp,
             int cur_dp,
             int max_vp,
             int cur_vp,
             char dead_symbol,
             char undead_symbol,
             bool is_dead,
             bool is_immortal,
             Point p);
};

class DragonStat : public Statistics,
                   public HPStat,
                   public MPStat,
                   public DPStat,
                   public VPStat,
                   public SymbolsStat,
                   public SpecialFlagsStat,
                   public CoordinateStat {
 public:
  DragonStat() = default;
  DragonStat(int max_hp,
             int cur_hp,
             int max_mp,
             int cur_mp,
             int max_dp,
             int cur_dp,
             int max_vp,
             int cur_vp,
             char dead_symbol,
             char undead_symbol,
             bool is_dead,
             bool is_immortal,
             Point p);
};

class WallStat : public Statistics,
                 public HPStat,
                 public SymbolsStat,
                 public SpecialFlagsStat,
                 public CoordinateStat {
 public:
  WallStat() = default;
  WallStat(int max_hp,
           int cur_hp,
           char dead_symbol,
           char undead_symbol,
           bool is_dead,
           bool is_immortal,
           Point p);
};

class LoadingStat {
 public:
  LoadingStat() = default;
  LoadingStat(std::string greeting, std::string hint);
  void setGreeting(std::string);
  std::string getGreeting();
  void setHint(std::string);
  std::string getHint();
 private:
  std::string greeting_;
  std::string hint_;
};

class MainMenuStat {
 public:
  MainMenuStat() = default;
  explicit MainMenuStat(std::vector<std::string> menu_items);
  void setMenuItems(std::vector<std::string>);
  std::vector<std::string> getMenuItems();
 private:
  std::vector<std::string> menu_items_;
};

class UIStat : public LoadingStat,
               public MainMenuStat,
               public Statistics {
 public:
  UIStat() = default;
  UIStat(std::string& greeting,
         std::string& hint,
         std::vector<std::string>& menu_items);
};

} // namespace stats
