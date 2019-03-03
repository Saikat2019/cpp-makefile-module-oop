#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point
{
public:
  Point();
  Point(int xval, int yval);
  void move(int dx, int dy);
  int get_x() const;
  int get_y() const;

private:
  int x;
  int y;
};

#endif
