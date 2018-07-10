//
// Created by truefinch on 11.07.18.
//

#include "Princess.h"

enums::CollideResult Princess::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if ((other_id == enums::FIRE_BALL_ID) or (other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID)) {
    result = enums::FIGHT;
  } else if ((other.getIsDead()) or (other_id == enums::PRINCESS_ID)) {
    result = enums::BARRIER;
  } else if (other_id == enums::HERO_ID) {
    result = enums::WIN;
  }
  return result;
}

Point Princess::findTarget() {
//  auto area = game_manager_.getArea();
  return {(double) (rand() % 3 - 1), (double) (rand() % 3 - 1)};
}

enums::CollideResult Princess::move() {
  Point princess_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea();
  Point dir = this->findTarget();
  Point other_pos = {princess_pos.x + dir.x, princess_pos.y + dir.y};
  std::shared_ptr<actor::Actor> other = area[other_pos.x][other_pos.y]->top();
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER: {
      break;
    }
    case enums::FREE: {
      game::GameManager::Instance().swap(princess_pos, other_pos);
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(enemy->getLevelPoints() * 10);
      if (enemy->getIsDead()) {
        game::GameManager::Instance().swap(princess_pos, other_pos);
      } else {
        this->setCurHealthPoints(this->getCurHealthPoints() - enemy->getDamagePoints());
        enemy->setCurScorePoints(this->level_points_ * 10);
      }
      break;
    }
    case enums::WIN: {
      //do nothing
      //this case is unreachable for Princess too
      break;
    }
    case enums::PICK: {
      if (other->getID() == enums::HP_POTION_ID)
        this->setCurHealthPoints(this->getCurHealthPoints() + this->getMaxHealthPoints() * this->getLevelPoints() / 10);
      else {
        this->setCurManaPoints(this->getCurManaPoints() + this->getMaxManaPoints() * this->getLevelPoints() / 10);
      }
      break;
    }
  }

  return collision;
}