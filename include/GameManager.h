//
// Created by truefinch on 17.05.18.
//
#pragma once

#include <UserInterface.h>
#include <Actors.h>
#include <Map.h>
#include <Config.h>

namespace game {

class GameManager {
 public:
  static GameManager& Instance();
  void Init(int rows, int cols);
  void Start();
  void Finish();
//  void loadMap
//  std::shared_ptr<config::Config> getConfiguration() const;
 private:
  GameManager() = default;
  ~GameManager() = default;

  GameManager(GameManager const&) = delete;
  GameManager& operator= (GameManager const&) = delete;

  enums::GameState game_state_ = enums::LOADING;
  std::vector<std::shared_ptr<actor::Actor>> actors_;
  std::shared_ptr<actor::Hero> hero_ptr_;
  ui::UserInterface ui_;
  config::Config game_config_;
  map::Map map_;

  int rows_ = 0, cols_ = 0;
};

} //namespace game
