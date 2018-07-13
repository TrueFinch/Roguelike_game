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
  json pause_menu_screen_config = config::Config::Instance().getPauseMenu();
  json sum_up_menu_screen_config = config::Config::Instance().getSumUpMenu();

  Loading::Instance().setGreeting(loading_screen_config["greeting"].get<std::string>());
  Loading::Instance().setHint(loading_screen_config["hint"].get<std::string>());

  MainMenu::Instance().setMenuItems(main_menu_screen_config["menu_items"].get<std::vector<std::string>>());

  PauseMenu::Instance().init(pause_menu_screen_config["menu_items"].get<std::vector<std::string>>());

  SumUpMenu::Instance().init(sum_up_menu_screen_config["for_winner"].get<std::string>(),
                             sum_up_menu_screen_config["for_loser"].get<std::string>(),
                             sum_up_menu_screen_config["top_text"].get<std::string>(),
                             sum_up_menu_screen_config["zombie"].get<std::string>(),
                             sum_up_menu_screen_config["dragon"].get<std::string>(),
                             sum_up_menu_screen_config["princess"].get<std::string>(),
                             sum_up_menu_screen_config["level"].get<std::string>(),
                             sum_up_menu_screen_config["step"].get<std::string>(),
                             sum_up_menu_screen_config["achievement"].get<std::string>(),
                             sum_up_menu_screen_config["score"].get<std::string>());
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
    case enums::PAUSE_MENU:
      GameField::Instance().update(ERR);
      game_state = PauseMenu::Instance().update(key);
      break;
    case enums::SUM_UP_MENU:
      game_state = SumUpMenu::Instance().update(key);
      break;
  }
  return game_state;
}

void ui::UserInterface::updateMap(const std::shared_ptr<std::vector<std::string>>& map,
                                  const std::shared_ptr<actor::ActiveActor> hero_pos, const int& hp_potion_amount, const int& mp_potion_amount) {
  GameField::Instance().updateMap(*map, hero_pos, hp_potion_amount, mp_potion_amount);
}


