//
// Created by truefinch on 06.07.18.
//
#pragma once

enum ActorID {HERO_ID = '@', ZOMBIE_ID = 'z', WALL_ID = '#', PRINCESS_ID = '*', DRAGON_ID = 'D', NOTHING_ID = '.'};
enum CollideEvent {DEATH};

enum GameState { LOADING = 0, MAIN_MENU, SETTINGS, EXIT, GAME_FIELD, PAUSE };
