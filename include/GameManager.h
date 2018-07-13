//
// Created by truefinch on 17.05.18.
//
#pragma once

#include <UserInterface.h>
#include <Event.h>
#include <Actors.h>
#include <Map.h>
#include <ActorFactory.h>

namespace game {

class GameManager {
 public:
  static GameManager& Instance();
  void init(int rows, int cols);
  void Start();
  void Finish();

  std::vector<std::vector<std::shared_ptr<actor::Actor>>> getArea(const Point&, int) const;
  void setLastPressedKey(int);
  int getLastPressedKey() const;
  void move(const Point& a, const Point& b) const;
  void loadMap() const;
 private:
  GameManager() = default;
  ~GameManager() = default;

  GameManager(GameManager const&) = delete;
  GameManager& operator= (GameManager const&) = delete;

  enums::GameState game_state_ = enums::LOADING;
  std::vector<std::shared_ptr<actor::ActiveActor>> actors_;
  int last_pressed_key_;

  int rows_ = 0, cols_ = 0, halfdelay_ = 1;
  bool real_time_ = false, fog_of_war_ = false;

};

} //namespace game
