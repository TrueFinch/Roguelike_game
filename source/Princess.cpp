//
// Created by truefinch on 11.07.18.
//

#include "Princess.h"

enums::CollideResult Princess::collide(actor::Actor& other) {
  enums::ActorID other_id = other.getID();
  if (other_id == enums::HERO_ID) {
    return enums::WIN;
  } else {
    return enums::BARRIER;
  }
}

enums::CollideResult Princess::collide(ActiveActor& other) {
  enums::CollideResult result;
  enums::ActorID other_id = other.getID();
  if (other_id == enums::HERO_ID) {
    result = enums::WIN;
  } else {
    result = enums::BARRIER;
  }
  return result;
}

enums::CollideResult Princess::collide(actor::PassiveActor& other) {
  return enums::BARRIER;
}

Point Princess::findTarget(const std::vector<std::vector<std::shared_ptr<actor::Actor>>>& area) {
  return {0, 0};
}

Event Princess::doTurn() {
  Event result = {this->getName(), this->getName(), enums::DO_NOTHING, -1};
  Point princess_pos = this->getPosition();
  auto area = game::GameManager::Instance().getArea(princess_pos, this->visibility_points_);
  Point dir = this->findTarget(area);
  Point other_pos = {princess_pos.x + dir.x, princess_pos.y + dir.y};
  int row = (int) princess_pos.x, col = (int) princess_pos.y,
      top_row_bound = row - std::min<int>(this->getVisibilityPoints(), row),
      left_row_bound = col - std::min<int>(this->getVisibilityPoints(), col);
  auto other = area[(int) other_pos.x - top_row_bound][(int) other_pos.y - left_row_bound];
  enums::CollideResult collision = this->collide(*other);

  switch (collision) {
    case enums::BARRIER: {
      break;
    }
    case enums::FREE: {
      break;
    }
    case enums::FIGHT: {
      break;
    }
    case enums::WIN: {
      break;
    }
    case enums::PICK: {
      break;
    }
  }

  return result;
}