//
// Created by truefinch on 27.05.18.
//

#ifndef ROGUELIKE_POINT_H
#define ROGUELIKE_POINT_H

#define EPS 2e-15

struct Point {
  Point();
  Point(double x, double y);
  double x, y;
  const bool operator<(const Point& rhs) const;
  const bool operator==(const Point& rhs) const;
};

#endif //ROGUELIKE_POINT_H
