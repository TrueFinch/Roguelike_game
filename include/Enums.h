//
// Created by truefinch on 06.07.18.
//
#pragma once

namespace enums {

  enum ActorID {HERO_ID = '@', ZOMBIE_ID = 'Z', WALL_ID = '#', PRINCESS_ID = 'P', DRAGON_ID = 'D', NOTHING_ID = '.'};
  enum CollideEvent {DEATH};

  enum GameState { LOADING = 0, MAIN_MENU, SETTINGS, EXIT, GAME_FIELD, PAUSE };
}; // namespace game_screen
