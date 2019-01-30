// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// Cartesian.h - definition of 2D cartesian coordinate class

#ifndef _CARTESIAN_H_
#define _CARTESIAN_H_

#include <string>
#include "Coordinate.h"

using namespace std;

class Cartesian : public Coordinate {
 public:
  // Construct the cartesian coordinate (x, y)
  Cartesian(double, double);

  // return a string representation
  virtual string ToString() const;

  // return the distance between the object and a second Cartesian point object
  double Distance(const Cartesian&) const;

 private:
  double x_;  // x coordinate
  double y_;  // y coordinate
};

#endif  // _CARTESIAN_H_
