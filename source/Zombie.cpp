//
// Created by truefinch on 10.07.18.
//

#include "Zombie.h"

enums::CollideResult Zombie::collide(actor::Actor& other) {
  return other.collide(*this);
}

enums::CollideResult Zombie::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.isDead()) {
    result = enums::PICK;
  } else if ((other_id == enums::HERO_ID) or (other_id == enums::FIRE_BALL_ID)) {
    result = enums::FIGHT;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID) or (other_id == enums::PRINCESS_ID)) {
    result = enums::BARRIER;
  }
  return result;
}

enums::CollideResult Zombie::collide(actor::PassiveActor& other) {
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

Point Zombie::findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>& area) {
//  auto area = game_manager_.getArea();
  return {(double) (rand() % 3 - 1), (double) (rand() % 3 - 1)};
}

Event Zombie::doTurn() {
  Event result = Event();
  if (this->isDead()) {
    return {this->getName(), this->getName(), enums::DO_NOTHING, -1};
  }
  Point zombie_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea(zombie_pos, this->visibility_points_);
  Point dir = this->findTarget(area);
  Point other_pos = {zombie_pos.x + dir.x, zombie_pos.y + dir.y};
  int row = (int) zombie_pos.x, col = (int) zombie_pos.y,
      top_row_bound = row - std::min<int>(this->getVisibilityPoints(), row),
      left_row_bound = col - std::min<int>(this->getVisibilityPoints(), col);
  auto other = area[(int) other_pos.x - top_row_bound][(int) other_pos.y - left_row_bound];
  enums::CollideResult collision = this->collide(*other);

  switch (collision) {
    case enums::BARRIER: {
      result = {this->getName(), this->getName(), enums::DO_NOTHING, -1};
      break;
    }
    case enums::FREE: {
      game::GameManager::Instance().move(zombie_pos, other_pos);
      result = {this->getName(), this->getName(), enums::MOVED, -1};
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      if (enemy->isDead()) {
        this->setCurScorePoints(this->cur_score_points_ + enemy->getLevelPoints() * enemy->getScorePointsMultiplier());
        game::GameManager::Instance().move(zombie_pos, other_pos);
      }
      result = {this->getName(), enemy->getName(), enums::ATTACKED, this->getDamagePoints()};
      break;
    }
    case enums::WIN: {
      result = {this->getName(), this->getName(), enums::DO_NOTHING, -1};
      break;
    }
    case enums::PICK: {
      std::shared_ptr<actor::ActiveActor> dead_body = std::static_pointer_cast<actor::ActiveActor>(other);
      this->setCurHealthPoints(
          this->getCurHealthPoints() + dead_body->getMaxHealthPoints() / dead_body->getScorePointsMultiplier()
      );
      result = {this->getName(), dead_body->getName(), enums::ATE, -1};
      break;
    }
  }

  return result;
}