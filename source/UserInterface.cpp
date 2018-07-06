//
// Created by truefinch on 04.06.18.
//

#include "UserInterface.h"

ui::UserInterface::UserInterface(stats::UIStat stat) {
  game_state_ = enums::LOADING;
  loading_.setGreeting(stat.getGreeting());
  loading_.setHint(stat.getHint());
  main_menu_.setMenuItems(stat.getMenuItems());
//  loading_ = game_screen::Loading();
//  main_menu_ = game_screen::MainMenu();
//  game_field_ = game_screen::GameField();
}

enums::GameState ui::UserInterface::update(int key) {
  switch (game_state_) {
    case enums::LOADING:
      game_state_ = loading_.update(key);
      if (game_state_ == enums::MAIN_MENU) {
        main_menu_.update(ERR);
      }
      break;
    case enums::MAIN_MENU:
      game_state_ = main_menu_.update(key);
      break;
    case enums::SETTINGS:
      break;
    case enums::EXIT:
      break;
      break;
    case enums::GAME_FIELD:
      break;
  }

}

enums::GameState ui::UserInterface::getGameState() const {
  return game_state_;
}

void ui::UserInterface::setGameState(enums::GameState new_game_state) {
  game_state_ = new_game_state;
}

