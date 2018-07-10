//
// Created by truefinch on 10.07.18.
//

#include "Hero.h"
#include "GameManager.h"

enums::CollideResult Hero::collide(ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.getIsDead()) {
    result = enums::FREE;
  } else if (other_id == enums::HERO_ID) {
    result = enums::BARRIER;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::DRAGON_ID)) {
    result = enums::FIGHT;
  } else if (other_id == enums::PRINCESS_ID) {
    result = enums::WIN;
  }
  return result;
}

enums::CollideResult Hero::move() {
  Point hero_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea();
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
  }

  Point other_pos = {hero_pos.x + dir.x, hero_pos.y + dir.y};
  std::shared_ptr<actor::Actor> other = area[(int) other_pos.x][(int) other_pos.y]->top();
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER: {
      break;
    }
    case enums::FREE: {
      game::GameManager::Instance().swap(hero_pos, other_pos);
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurScorePoints(this->cur_score_points_ + enemy->getLevelPoints() * 10);
      if (enemy->getIsDead()) {
        game::GameManager::Instance().swap(hero_pos, other_pos);
      } else {
        this->setCurHealthPoints(this->getCurHealthPoints() - enemy->getDamagePoints());
        enemy->setCurScorePoints(enemy->getCurScorePoints() + this->level_points_ * 10);
      }
      break;
    }
    case enums::WIN: {
      //do nothing
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

Point Hero::findTarget() {
  return {42, 42};
}