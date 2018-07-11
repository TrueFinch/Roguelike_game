//
// Created by truefinch on 11.07.18.
//

#include "ActorFactory.h"

factory::ActorFactory& factory::ActorFactory::Instance() {
  static ActorFactory self;
  return self;
}

std::shared_ptr<actor::Actor> factory::ActorFactory::CreateActor(enums::ActorID id, Point position, Point direction) {
  json actor_config;
  std::shared_ptr<actor::Actor> actor_ptr;
  Point pos = position;
  switch (id) {
    case enums::HERO_ID:
      actor_config = config::Config::Instance().getHero();
      actor_ptr = std::make_shared<Hero>(Hero(pos,
                                              actor_config["is_dead"].get<bool>(),
                                              actor_config["is_immortal"].get<bool>(),
                                              actor_config["live_symbol_code"].get<char>(),
                                              actor_config["dead_symbol_code"].get<char>(),
                                              actor_config["max_health_points"].get<int>(),
                                              actor_config["cur_health_points"].get<int>(),
                                              actor_config["max_mana_points"].get<int>(),
                                              actor_config["cur_mana_points"].get<int>(),
                                              actor_config["damage_points"].get<int>(),
                                              actor_config["visibility_points"].get<int>(),
                                              actor_config["level_points"].get<int>(),
                                              actor_config["max_score_points"].get<int>(),
                                              actor_config["cur_score_points"].get<int>(),
                                              actor_config["score_points_multiplier"].get<int>()
      ));
      break;
    case enums::ZOMBIE_ID:
      actor_config = config::Config::Instance().getZombie();
      actor_ptr = std::make_shared<Zombie>(Zombie(pos,
                                                  actor_config["is_dead"].get<bool>(),
                                                  actor_config["is_immortal"].get<bool>(),
                                                  actor_config["live_symbol_code"].get<char>(),
                                                  actor_config["dead_symbol_code"].get<char>(),
                                                  actor_config["max_health_points"].get<int>(),
                                                  actor_config["cur_health_points"].get<int>(),
                                                  actor_config["max_mana_points"].get<int>(),
                                                  actor_config["cur_mana_points"].get<int>(),
                                                  actor_config["damage_points"].get<int>(),
                                                  actor_config["visibility_points"].get<int>(),
                                                  actor_config["level_points"].get<int>(),
                                                  actor_config["max_score_points"].get<int>(),
                                                  actor_config["cur_score_points"].get<int>(),
                                                  actor_config["score_points_multiplier"].get<int>()
      ));
      break;
    case enums::DRAGON_ID:
      actor_config = config::Config::Instance().getDragon();
      actor_ptr = std::make_shared<Dragon>(Dragon(pos,
                                                  actor_config["is_dead"].get<bool>(),
                                                  actor_config["is_immortal"].get<bool>(),
                                                  actor_config["live_symbol_code"].get<char>(),
                                                  actor_config["dead_symbol_code"].get<char>(),
                                                  actor_config["max_health_points"].get<int>(),
                                                  actor_config["cur_health_points"].get<int>(),
                                                  actor_config["max_mana_points"].get<int>(),
                                                  actor_config["cur_mana_points"].get<int>(),
                                                  actor_config["damage_points"].get<int>(),
                                                  actor_config["visibility_points"].get<int>(),
                                                  actor_config["level_points"].get<int>(),
                                                  actor_config["max_score_points"].get<int>(),
                                                  actor_config["cur_score_points"].get<int>(),
                                                  actor_config["score_points_multiplier"].get<int>()
      ));
      break;
    case enums::PRINCESS_ID:
      actor_config = config::Config::Instance().getPrincess();
      actor_ptr = std::make_shared<Princess>(Princess(pos,
                                                      actor_config["is_dead"].get<bool>(),
                                                      actor_config["is_immortal"].get<bool>(),
                                                      actor_config["live_symbol_code"].get<char>(),
                                                      actor_config["dead_symbol_code"].get<char>(),
                                                      actor_config["max_health_points"].get<int>(),
                                                      actor_config["cur_health_points"].get<int>(),
                                                      actor_config["max_mana_points"].get<int>(),
                                                      actor_config["cur_mana_points"].get<int>(),
                                                      actor_config["damage_points"].get<int>(),
                                                      actor_config["visibility_points"].get<int>(),
                                                      actor_config["level_points"].get<int>(),
                                                      actor_config["max_score_points"].get<int>(),
                                                      actor_config["cur_score_points"].get<int>(),
                                                      actor_config["score_points_multiplier"].get<int>()
      ));
      break;
    case enums::FIRE_BALL_ID:
      actor_config = config::Config::Instance().getFireball();
      actor_ptr = std::make_shared<Fireball>(Fireball(pos,
                                                      actor_config["is_dead"].get<bool>(),
                                                      actor_config["is_immortal"].get<bool>(),
                                                      actor_config["live_symbol_code"].get<char>(),
                                                      actor_config["dead_symbol_code"].get<char>(),
                                                      actor_config["max_health_points"].get<int>(),
                                                      actor_config["cur_health_points"].get<int>(),
                                                      actor_config["max_mana_points"].get<int>(),
                                                      actor_config["cur_mana_points"].get<int>(),
                                                      actor_config["damage_points"].get<int>(),
                                                      actor_config["visibility_points"].get<int>(),
                                                      actor_config["level_points"].get<int>(),
                                                      actor_config["max_score_points"].get<int>(),
                                                      actor_config["cur_score_points"].get<int>(),
                                                      actor_config["score_points_multiplier"].get<int>(),
                                                      direction
      ));
      break;
    case enums::FLOOR_ID:
      actor_config = config::Config::Instance().getFloor();
      actor_ptr = std::make_shared<Floor>(Floor(pos,
                                                actor_config["live_symbol_code"].get<char>(),
                                                actor_config["dead_symbol_code"].get<char>(),
                                                actor_config["is_dead"].get<bool>(),
                                                actor_config["is_immortal"].get<bool>()
      ));
      break;
    case enums::WALL_ID:
      actor_config = config::Config::Instance().getWall();
      actor_ptr = std::make_shared<Wall>(Wall(pos,
                                              actor_config["live_symbol_code"].get<char>(),
                                              actor_config["dead_symbol_code"].get<char>(),
                                              actor_config["is_dead"].get<bool>(),
                                              actor_config["is_immortal"].get<bool>()
      ));
      break;
    case enums::HP_POTION_ID:
      actor_config = config::Config::Instance().getHealthPotion();
      actor_ptr = std::make_shared<HealthPotion>(HealthPotion(pos,
                                                              actor_config["live_symbol_code"].get<char>(),
                                                              actor_config["dead_symbol_code"].get<char>(),
                                                              actor_config["is_dead"].get<bool>(),
                                                              actor_config["is_immortal"].get<bool>(),
                                                              actor_config["health_points"].get<int>(),
                                                              actor_config["mana_points"].get<int>()
      ));
      break;
    case enums::MP_POTION_ID:
      actor_config = config::Config::Instance().getManaPotion();
      actor_ptr = std::make_shared<ManaPotion>(ManaPotion(pos,
                                                          actor_config["live_symbol_code"].get<char>(),
                                                          actor_config["dead_symbol_code"].get<char>(),
                                                          actor_config["is_dead"].get<bool>(),
                                                          actor_config["is_immortal"].get<bool>(),
                                                          actor_config["health_points"].get<int>(),
                                                          actor_config["mana_points"].get<int>()
      ));
      break;
  }

  return actor_ptr;
}
