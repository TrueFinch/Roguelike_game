//
// Created by truefinch on 04.06.18.
//

#include "UserInterface.h"
#include <utility>

ui::UserInterface& ui::UserInterface::Instance() {
  static UserInterface self;
  return self;
}

enums::GameState ui::UserInterface::update(enums::GameState game_state, int key) {
  switch (game_state) {
    case enums::LOADING:
      game_state = loading_.update(key);
      if (game_state == enums::MAIN_MENU) {
        main_menu_.update(ERR);
      }
      break;
    case enums::MAIN_MENU:
      game_state = main_menu_.update(key);
      break;
    case enums::SETTINGS:
      break;
    case enums::EXIT:
      break;
    case enums::GAME_FIELD:
      game_state = game_field_.update(key);
      break;
    case enums::PAUSE:
      break;
  }
  return game_state;
}

void ui::UserInterface::updateMap(std::shared_ptr<std::vector<std::string>> map, Point hero_pos) {
  game_field_.updateMap(std::move(map), hero_pos);
}


