//
// Created by truefinch on 27.05.18.
//

#include "Point.h"
#include <cmath>

Point::Point() {
  x = 42.0;
  y = 42.0;
}

Point::Point(double x, double y) : x{x}, y{y} {}

const bool Point::operator<(const Point& rhs) const {
  return ((this->x < rhs.x) && (this->y < rhs.y));
}

const bool Point::operator==(const Point& rhs) const {
  return ((fabs(this->x - rhs.x) <= EPS) && (fabs(this->y - rhs.y) <= EPS));
}