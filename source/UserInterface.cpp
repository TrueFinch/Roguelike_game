//
// Created by truefinch on 04.06.18.
//

#include "UserInterface.h"
#include <utility>

ui::UserInterface& ui::UserInterface::Instance() {
  static UserInterface self;
  return self;
}

void ui::UserInterface::init() {
  json loading_screen_config = config::Config::Instance().getLoading();
  json main_menu_screen_config = config::Config::Instance().getMainMenu();

}

enums::GameState ui::UserInterface::update(enums::GameState game_state, int key) {
  switch (game_state) {
    case enums::LOADING:
      game_state = Loading::Instance().update(key);
      if (game_state == enums::MAIN_MENU) {
        MainMenu::Instance().update(ERR);
      }
      break;
    case enums::MAIN_MENU:
      game_state = MainMenu::Instance().update(key);
      break;
    case enums::SETTINGS:
      break;
    case enums::EXIT:
      break;
    case enums::GAME_FIELD:
      game_state = GameField::Instance().update(key);
      break;
    case enums::PAUSE:
      break;
  }
  return game_state;
}

void ui::UserInterface::updateMap(const std::shared_ptr<std::vector<std::string>>& map,
                                  const std::shared_ptr<actor::ActiveActor> hero_pos) {
  GameField::Instance().updateMap(*map, hero_pos);
}


