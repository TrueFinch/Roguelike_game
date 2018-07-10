//
// Created by truefinch on 06.07.18.
//
#pragma once

namespace enums {

enum ActorID {
  HERO_ID = '@',
  ZOMBIE_ID = 'Z',
  PRINCESS_ID = 'P',
  DRAGON_ID = 'D',
  FIRE_BALL_ID = '*',
  FLOOR_ID = '.',
  WALL_ID = '#',
  HP_POTION_ID = 'H',
  MP_POTION_ID = 'M'
};
//enum MoveEvent { MOVED = 0, NOT_MOVED, COLLIDE };

enum CollideResult {FREE = 0, BARRIER, FIGHT, PICK, WIN};

enum GameState { LOADING = 0, MAIN_MENU, SETTINGS, EXIT, GAME_FIELD, PAUSE};
}; // namespace game_screen
