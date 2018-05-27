//
// Created by truefinch on 27.05.18.
//

#ifndef ROGUELIKE_STATISTICS_H
#define ROGUELIKE_STATISTICS_H

#include <Point.h>

namespace stats {

//health points statistics
class HPStat {
 public:
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
  void setMaxVP(int);
  int getMaxVP() const;
  void setCurVP(int);
  int getCurVP() const;
 protected:
  int max_visibility_points_ = 0;
  int cur_visibility_points_ = 0;
};

//is actor dead or immortal statistics
class FStat {
 public:
  void setDead(bool);
  bool isDead() const;
  void setImmortal(bool);
  bool isImmortal() const;
 protected:
  bool is_dead_ = false;
  bool is_immortal_ = false;
};

//statistics of actor's symbol
class SStat {
 public:
  void setDeadSymbol(char);
  char getDeadSymbol() const;
  void setUndeadSymbol(char);
  bool getUndeadSymbol() const;
 protected:
  bool dead_symbol_ = false;
  bool undead_symbol_ = false;
};

//actor's coordinate statistics
class CStat {
 public:
  void setCoord(Point p);
  Point getCoord() const;
 protected:
  Point coordinate_;
};

class HeroStat
    : public HPStat, public MPStat, public DPStat, public VPStat, public FStat, public SStat, public CStat {
};

class PrincessStat : public MPStat, public VPStat, public FStat, public SStat, public CStat {};

class ZombieStat : public HPStat, public DPStat, public VPStat, public FStat, public SStat, public CStat {};

class DragonStat
    : public HPStat, public MPStat, public DPStat, public VPStat, public FStat, public SStat, public CStat {
};

class WallStat : public HPStat, public FStat, public SStat {};

} // namespace stats
#endif //ROGUELIKE_STATISTICS_H
