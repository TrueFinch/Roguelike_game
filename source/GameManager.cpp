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
  //TODO: Add initialization of UI
  //TODO: Add loading of map and configuration
//  ui::UserInterface::Instance().init();
//  hero_ptr_ = map::Map::Instance().loadMap(actors_, game_config_);
  game_state_ = enums::LOADING;

  initscr();
  clear();
  cbreak();
  keypad(stdscr, true);
  noecho();
  curs_set(0);
  halfdelay(1);
  resize_term(rows, cols);
}

void game::GameManager::Start() {
  int key = ERR;

  while (game_state_ != enums::EXIT) {
    this->game_state_ = ui::UserInterface::Instance().update(this->game_state_, key);
    key = getch();
    if (game_state_ == enums::GAME_FIELD) {
      this->setLastPressedKey(key);
      if (key != ERR) {
        if (!map::Map::Instance().loaded) {
          std::vector<enums::ActorID> actorsID;
          std::vector<Point> actors_pos;
          map::Map::Instance().loadMap(actorsID,
                                       actors_pos,
                                       "/home/truefinch/CLionProjects/Roguelike_game/map/level_1.txt");
          for (int i = 0; i < (int) actorsID.size(); ++i) {
            std::shared_ptr<actor::Actor> actor_ptr;
            actor_ptr = factory::ActorFactory::Instance().CreateActor(actorsID[i], actors_pos[i]);
            enums::ActorID id = actor_ptr->getID();
            map::Map::Instance().addActorToCell(actor_ptr, actors_pos[i]);
            if ((id == enums::ZOMBIE_ID) or (id == enums::DRAGON_ID) or (id == enums::PRINCESS_ID)) {
              this->actors_.push_back(std::static_pointer_cast<actor::ActiveActor>(actor_ptr));
            } else if (id == enums::HERO_ID) {
              this->hero_ = std::static_pointer_cast<actor::ActiveActor>(actor_ptr);
            }
          }
        }
        hero_->move();
        for (int i = 0; i < (int) this->actors_.size(); ++i) {
          actors_[i]->move();
        }
      }
      ui::UserInterface::Instance().updateMap(map::Map::Instance().getMapView(), this->hero_);
//      ui::UserInterface::Instance().update(this->game_state_, key);
    }
  }
  Finish();
}

void game::GameManager::Finish() {
  clear();
  endwin();
}

std::vector<std::vector<std::shared_ptr<map::Cell>>> game::GameManager::getArea() const {
  return std::vector<std::vector<std::shared_ptr<map::Cell>>>();
}

void game::GameManager::setLastPressedKey(int key) {
  this->last_pressed_key_ = key;
}

int game::GameManager::getLastPressedKey() const {
  return this->last_pressed_key_;
}

void game::GameManager::swap(Point a, Point b) const {
  map::Map::Instance().swap(a, b);
}
