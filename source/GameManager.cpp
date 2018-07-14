//
// Created by truefinch on 17.05.18.
//


#include <ncurses.h>
#include "GameManager.h"

game::GameManager& game::GameManager::Instance() {
  static GameManager self;
  return self;
}

void game::GameManager::init(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  game_state_ = enums::LOADING;

  config::Config::Instance().initGameManager(
      "/home/truefinch/CLionProjects/Roguelike_game/configuration/config_game.json");
  json game_manager_config = config::Config::Instance().getGameManager();

  real_time_ = game_manager_config["Real-time"].get<bool>();
  fog_of_war_ = game_manager_config["Fog_of_war"].get<bool>();
  halfdelay_ = game_manager_config["halfdelay"].get<int>();
  map_generator_canvas_height_ = game_manager_config["map_generator_canvas_height"].get<int>();
  map_generator_canvas_width_ = game_manager_config["map_generator_canvas_width"].get<int>();
  path_to_saved_map_ = game_manager_config["path_to_save_map"].get<std::string>();
  path_to_ui_config_ = game_manager_config["path_to_ui_config"].get<std::string>();

  config::Config::Instance().initUI(path_to_ui_config_);
  ui::UserInterface::Instance().init();

  initscr();
  clear();
  cbreak();
  keypad(stdscr, true);
  noecho();
  curs_set(0);
  halfdelay(5);
  resize_term(rows, cols);
}

void game::GameManager::Start() {
  int key = ERR;

  while (game_state_ != enums::EXIT) {
    if (game_state_ == enums::MAIN_MENU) {
      map::Map::Instance().loaded = false;
    }
    this->game_state_ = ui::UserInterface::Instance().update(this->game_state_, key);
    key = getch();
    if (game_state_ == enums::GAME_FIELD) {
      this->setLastPressedKey(key);
      if (!map::Map::Instance().loaded) {
        game::GameManager::Instance().loadMap();
      }
      Event turn_result;
      bool is_won = false;
      std::shared_ptr<Hero> h = std::static_pointer_cast<Hero>(this->actors_[0]);
      if ((key != ERR) or real_time_) {
//      if (true) {
        for (int i = 0; i < (int) this->actors_.size(); ++i) {
          turn_result = actors_[i]->doTurn();
          switch (turn_result.getAction()) {
            case enums::WON:
              game_state_ = enums::SUM_UP_MENU;
              printf("%s", "YOU WON");
              is_won = true;
              break;
            case enums::DIED:
              game_state_ = enums::SUM_UP_MENU;
              printf("%s", "YOU DIED");
              break;
            case enums::DO_NOTHING:
              //do nothing
              break;
            case enums::PICKED_UP:
              break;
            case enums::ATTACKED:
              break;
            case enums::DRANK:
              break;
            case enums::MOVED:
              break;
            case enums::ATE:
              break;
          }
        }
      }
      std::vector<int> hero_stats = h->getStats();
      SumUpMenu::Instance().updateStats(hero_stats[0],
                                        hero_stats[1],
                                        hero_stats[2],
                                        hero_stats[3],
                                        hero_stats[4],
                                        hero_stats[5],
                                        h->getAchievements(),
                                        is_won);
      ui::UserInterface::Instance().updateMap(map::Map::Instance().getMapView(),
                                              this->actors_[0],
                                              h->getHpPotionAmount(),
                                              h->getMpPotionAmount());
    }
  }
  Finish();
}

void game::GameManager::Finish() {
  clear();
  endwin();
}

std::vector<std::vector<std::shared_ptr<actor::Actor>>> game::GameManager::getArea(const Point& coord,
                                                                                   const int radius) const {
  return map::Map::Instance().getArea(coord, radius);
}

void game::GameManager::setLastPressedKey(int key) {
  this->last_pressed_key_ = key;
}

int game::GameManager::getLastPressedKey() const {
  return this->last_pressed_key_;
}

void game::GameManager::move(const Point& a, const Point& b) const {
  map::Map::Instance().move(a, b);
}

void game::GameManager::loadMap() const {
  GameManager& game_manager = game::GameManager::Instance();
  MapGenerator& map_generator = MapGenerator::Instance();

  map_generator.setSize(map_generator_canvas_height_, map_generator_canvas_width_);
  map_generator.initCanvas();
  map_generator.readTiles();
  map_generator.fillCanvas();
  map_generator.addActors();
  map_generator.saveMap(path_to_saved_map_);

  std::vector<enums::ActorID> actorsID;
  std::vector<Point> actors_pos;

  map::Map::Instance().loadMap(actorsID, actors_pos, path_to_saved_map_);

  config::Config::Instance().initActors(
      "/home/truefinch/CLionProjects/Roguelike_game/configuration/config_level_1.json");

  for (int i = 0; i < (int) actorsID.size(); ++i) {
    std::shared_ptr<actor::Actor> actor_ptr;
    actor_ptr = factory::ActorFactory::Instance().CreateActor(actorsID[i], actors_pos[i]);
    enums::ActorID id = actor_ptr->getID();
    map::Map::Instance().addActorToCell(actor_ptr, actors_pos[i]);
    if ((id == enums::ZOMBIE_ID) or (id == enums::DRAGON_ID) or (id == enums::PRINCESS_ID)
        or (id == enums::FIRE_BALL_ID)) {
      game_manager.actors_.push_back(std::static_pointer_cast<actor::ActiveActor>(actor_ptr));
    } else if (id == enums::HERO_ID) {
      game_manager.actors_.insert(actors_.begin(), std::static_pointer_cast<actor::ActiveActor>(actor_ptr));
    }
  }
  map::Map::Instance().loaded = true;
}

std::vector<std::shared_ptr<actor::ActiveActor>>& game::GameManager::getActors() {
  return actors_;
}
