//
// Created by truefinch on 10.07.18.
//

#include "Hero.h"
#include "GameManager.h"

#define KEY_1 49
#define KEY_2 50

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

enums::CollideResult Hero::collide(actor::Actor& other) {
  enums::ActorID other_id = other.getID();
  if ((other_id == enums::HP_POTION_ID) or (other_id == enums::MP_POTION_ID)) {
    return enums::PICK;
  } else if (other_id == enums::PRINCESS_ID) {
    return enums::WIN;
  } else if ((other_id == enums::DRAGON_ID) or (other_id == enums::ZOMBIE_ID) or (other_id == enums::FIRE_BALL_ID)) {
    return enums::FIGHT;
  } else if (other_id == enums::WALL_ID) {
    return enums::BARRIER;
  } else {
    return enums::FREE;
  }
}

enums::CollideResult Hero::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.isDead()) {
    result = enums::FREE;
  } else if (other_id == enums::HERO_ID) {
    result = enums::BARRIER;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID) or (other_id == enums::FIRE_BALL_ID)) {
    result = enums::FIGHT;
  } else if (other_id == enums::PRINCESS_ID) {
    result = enums::WIN;
  }
  return result;
}

enums::CollideResult Hero::collide(actor::PassiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.isDead() or (other_id == enums::FLOOR_ID)) {
    result = enums::FREE;
  } else if ((other_id == enums::HP_POTION_ID) or (other_id == enums::MP_POTION_ID)) {
    result = enums::PICK;
  } else if (other_id == enums::WALL_ID) {
    result = enums::BARRIER;
  }
  return result;
}

enums::CollideResult Hero::collide(actor::SpellActor&) {
  return enums::FIGHT;
}

enums::CollideResult Hero::collide(actor::CollectableActor&) {
  return enums::PICK;
}

Event Hero::doTurn() {
  Event result = Event();
  if (this->isDead()) {
    return Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
  }
  Point hero_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea(hero_pos, this->getVisibilityPoints());
  int key = game::GameManager::Instance().getLastPressedKey();
  Point dir = {0, 0};

  if (key == KEY_UP) {
    dir.x -= 1;
  } else if (key == KEY_DOWN) {
    dir.x += 1;
  } else if (key == KEY_LEFT) {
    dir.y -= 1;
  } else if (key == KEY_RIGHT) {
    dir.y += 1;
  } else if (key == KEY_1) {
    if (hp_potion_amount_ > 1) {
      std::shared_ptr<actor::Actor> actor = factory::ActorFactory::Instance().CreateActor(enums::HP_POTION_ID);
      std::shared_ptr<actor::CollectableActor> potion = std::static_pointer_cast<actor::CollectableActor>(actor);
      this->setCurHealthPoints(this->getCurHealthPoints() + potion->getHealthPoints());
      --hp_potion_amount_;
      result = Event(this->getName(), potion->getName(), enums::DRANK, potion->getHealthPoints());
    }
  } else if (key == KEY_2) {
    if (mp_potion_amount_ > 1) {
      std::shared_ptr<actor::Actor> actor = factory::ActorFactory::Instance().CreateActor(enums::MP_POTION_ID);
      std::shared_ptr<actor::CollectableActor> potion = std::static_pointer_cast<actor::CollectableActor>(actor);
      this->setCurManaPoints(this->getCurManaPoints() + potion->getManaPoints());
      --mp_potion_amount_;
      result = Event(this->getName(), potion->getName(), enums::DRANK, potion->getManaPoints());
    }
  }

  Point other_pos = {hero_pos.x + dir.x, hero_pos.y + dir.y};
  int row = (int) hero_pos.x, col = (int) hero_pos.y,
      top_row_bound = row - std::min<int>(this->getVisibilityPoints(), row),
      left_row_bound = col - std::min<int>(this->getVisibilityPoints(), col);
  auto other = area[(int) other_pos.x - top_row_bound][(int) other_pos.y - left_row_bound];
  enums::CollideResult collision = this->collide(*other);

  if (key == KEY_W) {
    std::shared_ptr<actor::Actor> new_fireball =
        factory::ActorFactory::Instance().CreateActor(enums::FIRE_BALL_ID,
                                                      {hero_pos.x - 1, hero_pos.y},
                                                      {-1, 0});
    other = area[(int) hero_pos.x - 1 - top_row_bound][(int) hero_pos.y - left_row_bound];
    collision = new_fireball->collide(*other);
    if (collision == enums::FREE) {
      auto cast_fireball = std::static_pointer_cast<actor::ActiveActor>(new_fireball);
      if (this->getCurManaPoints() >= cast_fireball->getCurManaPoints()) {
        game::GameManager::Instance().getActors().push_back(cast_fireball);
        map::Map::Instance().addActorToCell(new_fireball, {hero_pos.x - 1, hero_pos.y});
        this->setCurManaPoints(this->getCurManaPoints() - cast_fireball->getCurManaPoints());
      }
    }
  } else if (key == KEY_A) {
    std::shared_ptr<actor::Actor> new_fireball =
        factory::ActorFactory::Instance().CreateActor(enums::FIRE_BALL_ID,
                                                      {hero_pos.x, hero_pos.y - 1},
                                                      {0, -1});
    other = area[(int) hero_pos.x - top_row_bound][(int) hero_pos.y - 1 - left_row_bound];
    collision = new_fireball->collide(*other);
    if (collision == enums::FREE) {
      auto cast_fireball = std::static_pointer_cast<actor::ActiveActor>(new_fireball);
      if (this->getCurManaPoints() >= cast_fireball->getCurManaPoints()) {
        game::GameManager::Instance().getActors().push_back(cast_fireball);
        map::Map::Instance().addActorToCell(new_fireball, {hero_pos.x, hero_pos.y - 1});
        this->setCurManaPoints(this->getCurManaPoints() - cast_fireball->getCurManaPoints());
      }
    }
  } else if (key == KEY_S) {
    std::shared_ptr<actor::Actor> new_fireball =
        factory::ActorFactory::Instance().CreateActor(enums::FIRE_BALL_ID,
                                                      {hero_pos.x + 1, hero_pos.y},
                                                      {1, 0});
    other = area[(int) hero_pos.x + 1 - top_row_bound][(int) hero_pos.y - left_row_bound];
    collision = new_fireball->collide(*other);
    if (collision == enums::FREE) {
      auto cast_fireball = std::static_pointer_cast<actor::ActiveActor>(new_fireball);
      if (this->getCurManaPoints() >= cast_fireball->getCurManaPoints()) {
        game::GameManager::Instance().getActors().push_back(cast_fireball);
        map::Map::Instance().addActorToCell(new_fireball, {hero_pos.x + 1, hero_pos.y});
        this->setCurManaPoints(this->getCurManaPoints() - cast_fireball->getCurManaPoints());
      }
    }
  } else if (key == KEY_D) {
    std::shared_ptr<actor::Actor> new_fireball =
        factory::ActorFactory::Instance().CreateActor(enums::FIRE_BALL_ID,
                                                      {hero_pos.x, hero_pos.y + 1},
                                                      {0, 1});
    other = area[(int) hero_pos.x - top_row_bound][(int) hero_pos.y + 1 - left_row_bound];
    collision = new_fireball->collide(*other);
    if (collision == enums::FREE) {
      auto cast_fireball = std::static_pointer_cast<actor::ActiveActor>(new_fireball);
      if (this->getCurManaPoints() >= cast_fireball->getCurManaPoints()) {
        game::GameManager::Instance().getActors().push_back(cast_fireball);
        map::Map::Instance().addActorToCell(new_fireball, {hero_pos.x, hero_pos.y + 1});
        this->setCurManaPoints(this->getCurManaPoints() - cast_fireball->getCurManaPoints());
      }
    }
  }

  switch (collision) {
    case enums::BARRIER: {
      result = Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
      break;
    }
    case enums::FREE: {
      result = Event(this->getName(), this->getName(), enums::MOVED, -1);
      game::GameManager::Instance().move(hero_pos, other_pos);
      ++steps_made_;
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      if (enemy->isDead()) {
        if (enemy->getID() == enums::ZOMBIE_ID) {
          ++zombie_killed_;
        } else {
          ++dragon_killed_;
        }
        ++steps_made_;
        this->setCurScorePoints(this->cur_score_points_ + enemy->getLevelPoints() * enemy->getScorePointsMultiplier());
        game::GameManager::Instance().move(hero_pos, other_pos);
      }
      result = Event(this->getName(), enemy->getName(), enums::ATTACKED, this->getDamagePoints());
      break;
    }
    case enums::WIN: {
      ++princess_rescued_;
      result = Event(this->getName(), this->getName(), enums::WON, -1);
      break;
    }
    case enums::PICK: {
      std::shared_ptr<actor::CollectableActor> potion = std::static_pointer_cast<actor::CollectableActor>(other);
      if (other->getID() == enums::HP_POTION_ID) {
        ++hp_potion_amount_;
      } else if (other->getID() == enums::MP_POTION_ID) {
        ++mp_potion_amount_;
      }
      potion->isDead(true);
      game::GameManager::Instance().move(hero_pos, other_pos);
      ++steps_made_;
      result = Event(this->getName(), potion->getName(), enums::PICKED_UP, -1);
      break;
    }
  }

  return result;
}

Point Hero::findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>& area) {
  return {42, 42};
}

const std::vector<int> Hero::getStats() const {
  std::vector<int> result;
  result.push_back(zombie_killed_);
  result.push_back(dragon_killed_);
  result.push_back(princess_rescued_);
  result.push_back(level_points_);
  result.push_back(cur_score_points_);
  result.push_back(steps_made_);
  return result;
}

const std::vector<bool>& Hero::getAchievements() const {
  return achievements_;
}

const int Hero::getHpPotionAmount() const {
  return hp_potion_amount_;
}

const int Hero::getMpPotionAmount() const {
  return mp_potion_amount_;
}
