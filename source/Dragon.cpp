//
// Created by truefinch on 10.07.18.
//

#include <cstdlib>
#include "Dragon.h"

enums::CollideResult Dragon::collide(actor::Actor& other) {
  enums::ActorID other_id = other.getID();
  if (other_id == enums::FIRE_BALL_ID) {
    return enums::PICK;
  } else if ((other_id == enums::WALL_ID) or (other_id == enums::PRINCESS_ID) or (other_id == enums::DRAGON_ID)
      or (other_id == enums::ZOMBIE_ID)) {
    return enums::BARRIER;
  } else if (other_id == enums::HERO_ID) {
    return enums::FIGHT;
  } else {
    return enums::FREE;
  }
}

enums::CollideResult Dragon::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if ((other_id == enums::HERO_ID)) {
    result = enums::FIGHT;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID) or (other_id == enums::PRINCESS_ID)) {
    result = enums::BARRIER;
  } else if (other.isDead()) {
    result = enums::FREE;
  } else if (other_id == enums::FIRE_BALL_ID) {
    result = enums::PICK;
  }
  return result;
}

enums::CollideResult Dragon::collide(actor::PassiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.isDead() or (other_id == enums::FLOOR_ID) or (other_id == enums::HP_POTION_ID)
      or (other_id == enums::MP_POTION_ID)) {
    result = enums::FREE;
  } else if (other_id == enums::WALL_ID) {
    result = enums::BARRIER;
  }
  return result;
}

Point Dragon::findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>& area) {
//  auto area = game_manager_.getArea();
  return {(double) (rand() % 3 - 1), (double) (rand() % 3 - 1)};
}

Event Dragon::doTurn() {
  if (this->isDead()) {
    return Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
  }
  Point dragon_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea(dragon_pos, this->visibility_points_);
  Point dir = this->findTarget(area);

  Point other_pos = {dragon_pos.x + dir.x, dragon_pos.y + dir.y};
  int row = (int) dragon_pos.x, col = (int) dragon_pos.y,
      top_row_bound = row - std::min<int>(this->getVisibilityPoints(), row),
      left_row_bound = col - std::min<int>(this->getVisibilityPoints(), col);
  auto other = area[(int) other_pos.x - top_row_bound][(int) other_pos.y - left_row_bound];
  enums::CollideResult collision = this->collide(*other);

  switch (collision) {
    case enums::BARRIER: {
      return Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
      break;
    }
    case enums::FREE: {
      game::GameManager::Instance().move(dragon_pos, other_pos);
      return Event(this->getName(), this->getName(), enums::MOVED, -1);
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      if (enemy->isDead()) {
        this->setCurScorePoints(enemy->getLevelPoints() * enemy->getScorePointsMultiplier());
        game::GameManager::Instance().move(dragon_pos, other_pos);
        return Event(this->getName(), enemy->getName(), enums::DIED, this->getDamagePoints());
      }
      break;
    }
    case enums::WIN: {
      return Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
      break;
    }
    case enums::PICK: {
      std::shared_ptr<actor::SpellActor> fireball = std::static_pointer_cast<actor::SpellActor>(other);
      this->setCurHealthPoints(this->getCurHealthPoints() + fireball->getCurHealthPoints());
      fireball->setCurHealthPoints(0);
      return Event(this->getName(), fireball->getName(), enums::ATE, -1);
      break;
    }
  }
  return Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
}