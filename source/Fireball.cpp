//
// Created by truefinch on 11.07.18.
//

#include "Fireball.h"

enums::CollideResult Fireball::collide(actor::ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.getIsDead()) {
    result = enums::FREE;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::PRINCESS_ID) or (other_id == enums::HERO_ID)) {
    result = enums::FIGHT;
  } else if (other_id == enums::DRAGON_ID) {
    result = enums::PICK;
  }
  return result;
}

enums::CollideResult Fireball::move() {
  Point fireball_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea();
  Point dir = this->findTarget();
  Point other_pos = {fireball_pos.x + dir.x, fireball_pos.y + dir.y};
  std::shared_ptr<actor::Actor> other = area[other_pos.x][other_pos.y]->top();
  enums::CollideResult collision = this->collide(*this);

  switch (collision) {
    case enums::BARRIER: {
      this->setDirection({this->getDirection().y, this->getDirection().x});
      break;
    }
    case enums::FREE: {
      game::GameManager::Instance().swap(fireball_pos, other_pos);
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurHealthPoints(0);
      this->setIsDead(true);
      break;
    }
    case enums::WIN: {
      //do nothing
      //this case is unreachable for Fireball too
      break;
    }
    case enums::PICK: {
      //Fireballs heal the Dragon
      std::shared_ptr<actor::ActiveActor> dragon = std::static_pointer_cast<actor::ActiveActor>(other);
      this->setCurHealthPoints(this->getCurHealthPoints() + this->getCurHealthPoints());
      break;
    }
  }
  return collision;
}