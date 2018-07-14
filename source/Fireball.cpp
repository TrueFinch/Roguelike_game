//
// Created by truefinch on 11.07.18.
//

#include "Fireball.h"

enums::CollideResult Fireball::collide(actor::Actor& other) {
  enums::ActorID other_id = other.getID();
  if (other_id == enums::DRAGON_ID) {
    return enums::PICK;
  } else if ((other_id == enums::WALL_ID) or (other_id == enums::PRINCESS_ID)) {
    return enums::BARRIER;
  } else if ((other_id == enums::HERO_ID) or (other_id == enums::ZOMBIE_ID)) {
    return enums::FIGHT;
  } else {
    return enums::FREE;
  }
}

enums::CollideResult Fireball::collide(actor::ActiveActor& other) {
  enums::CollideResult result = enums::BARRIER;
  enums::ActorID other_id = other.getID();
  if (other.isDead()) {
    result = enums::FREE;
  } else if ((other_id == enums::ZOMBIE_ID) or (other_id == enums::HERO_ID)) {
    result = enums::FIGHT;
  } else if (other_id == enums::DRAGON_ID) {
    result = enums::PICK;
  }
  return result;
}

enums::CollideResult Fireball::collide(actor::PassiveActor& other) {
  enums::CollideResult result = enums::FREE;
  enums::ActorID other_id = other.getID();
  if (other.isDead() or (other_id == enums::FLOOR_ID)) {
    result = enums::FREE;
  } else if (other_id == enums::WALL_ID) {
    result = enums::BARRIER;
  }
  return result;
}

enums::CollideResult Fireball::collide(actor::SpellActor&) {
  return enums::FIGHT;
}

enums::CollideResult Fireball::collide(actor::CollectableActor&) {
  return enums::FREE;
}

Event Fireball::doTurn() {
  Event result = Event();
  if (this->isDead()) {
    return Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
  }
  Point fireball_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea(fireball_pos, this->visibility_points_);
  Point dir = this->findTarget(area);
  Point other_pos = {fireball_pos.x + dir.x, fireball_pos.y + dir.y};
  int row = (int) fireball_pos.x, col = (int) fireball_pos.y,
      top_row_bound = row - std::min<int>(this->getVisibilityPoints(), row),
      left_row_bound = col - std::min<int>(this->getVisibilityPoints(), col);
  auto other = area[(int) other_pos.x - top_row_bound][(int) other_pos.y - left_row_bound];
//  std::shared_ptr<actor::Actor> other = area[other_pos.x][other_pos.y];
  enums::CollideResult collision = this->collide(*other);

  switch (collision) {
    case enums::BARRIER: {
      this->isDead(true);
      result = Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
      break;
    }
    case enums::FREE: {
      game::GameManager::Instance().move(fireball_pos, other_pos);
      result = Event(this->getName(), this->getName(), enums::MOVED, -1);
      break;
    }
    case enums::FIGHT: {
      std::shared_ptr<actor::ActiveActor> enemy = std::static_pointer_cast<actor::ActiveActor>(other);
      enemy->setCurHealthPoints(enemy->getCurHealthPoints() - this->getDamagePoints());
      this->setCurHealthPoints(0);
      this->isDead(true);
      result = Event(this->getName(), enemy->getName(), enums::ATTACKED, this->getDamagePoints());
      break;
    }
    case enums::WIN: {
      result = Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
      break;
    }
    case enums::PICK: {
      std::shared_ptr<actor::ActiveActor> dragon = std::static_pointer_cast<actor::ActiveActor>(other);
      this->setCurHealthPoints(this->getCurHealthPoints() + this->getCurHealthPoints());
      result = Event(this->getName(), this->getName(), enums::DO_NOTHING, -1);
      break;
    }
  }
  return result;
}