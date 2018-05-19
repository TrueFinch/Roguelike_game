//
// Created by truefinch on 20.05.18.
//

#include <Actors.h>
#include <cmath>

actor::Point::Point() {
  this->x = 42.0;
  this->y = 42.0;
}

actor::Point::Point(double x, double y) : x{x}, y{y} {}

const bool actor::Point::operator<(const Point& rhs) const {
  return ((this->x < rhs.x) && (this->y < rhs.y));
}

const bool actor::Point::operator==(const Point& rhs) const {
  return ((fabs(this->x - rhs.x) <= EPS) && (fabs(this->y - rhs.y) <= EPS));
}