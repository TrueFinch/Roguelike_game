//
// Created by truefinch on 10.07.18.
//

#include "Zombie.h"

enums::CollideResult Zombie::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.getIsDead()) {
    result = enums::PICK;
  } else if ((other_id == enums::HERO_ID)) {
    result = enums::FIGHT;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID) or (other_id == enums::PRINCESS_ID)) {
    result = enums::BARRIER;
  }
  return result;
}

Point Zombie::findTarget() {
//  auto area = game_manager_.getArea();
  return {(double) (rand() % 3 - 1), (double) (rand() % 3 - 1)};
}

enums::CollideResult Zombie::move() {
  Point zombie_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea();
  Point dir = this->findTarget();
  Point other_pos = {zombie_pos.x + dir.x, zombie_pos.y + dir.y};
  std::shared_ptr<Actor> other = area[other_pos.x][other_pos.y]->top();
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER: {
      break;
    }
    case enums::FREE: {
      game::GameManager::Instance().swap(zombie_pos, other_pos);
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(this->cur_score_points_ + enemy->getLevelPoints() * 10);
      if (enemy->getIsDead()) {
        game::GameManager::Instance().swap(zombie_pos, other_pos);
      } else {
        this->setCurHealthPoints(this->getCurHealthPoints() - enemy->getDamagePoints());
        enemy->setCurScorePoints(enemy->getCurScorePoints() + this->level_points_ * 10);
      }
      break;
    }
    case enums::WIN: {
      //do nothing
      //this case is unreachable for zombie
      break;
    }
    case enums::PICK: {
      this->setCurHealthPoints(this->getCurHealthPoints() + this->getMaxHealthPoints() / 20);
      break;
    }
  }
  return collision;
}