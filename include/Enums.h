//
// Created by truefinch on 06.07.18.
//
#pragma once

#define KEY_ENT 10
#define KEY_ESC 27

namespace enums {

enum ActorID {
  HERO_ID = '@',
  ZOMBIE_ID = 'Z',
  DRAGON_ID = 'D',
  PRINCESS_ID = 'P',
  FIRE_BALL_ID = '*',
  FLOOR_ID = '.',
  WALL_ID = '#',
  HP_POTION_ID = 'H',
  MP_POTION_ID = 'M'
};
//enum MoveEvent { MOVED = 0, NOT_MOVED, COLLIDE };

enum CollideResult { FREE = 0, BARRIER, FIGHT, PICK, WIN };

enum TurnResult { WON = 0, DIED, DO_NOTHING, PICKED_UP, ATTACKED, DRANK, MOVED, ATE };

enum GameState { LOADING = 0, MAIN_MENU, SETTINGS, EXIT, GAME_FIELD, PAUSE_MENU, SUM_UP_MENU };
}; // namespace game_screen
