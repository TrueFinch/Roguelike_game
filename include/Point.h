//
// Created by truefinch on 27.05.18.
//
#pragma once

#define EPS 2e-15

struct Point {
  Point();
  Point(double x, double y);
  double x, y;
  const bool operator<(const Point& rhs) const;
  const bool operator==(const Point& rhs) const;
};
