//
// Created by truefinch on 06.07.18.
//
#pragma once

namespace enums {

enum ActorID {
  HERO_ID = '@',
  ZOMBIE_ID = 'Z',
  WALL_ID = '#',
  PRINCESS_ID = 'P',
  DRAGON_ID = 'D',
  NOTHING_ID = '.',
  FIRE_BALL_ID = '*',
  HP_POTION = 'H',
  MP_POTION = 'M'
};
enum MoveEvent { MOVED = 0, NOT_MOVED = 0};

enum GameState { LOADING = 0, MAIN_MENU, SETTINGS, EXIT, GAME_FIELD, PAUSE };
}; // namespace game_screen
