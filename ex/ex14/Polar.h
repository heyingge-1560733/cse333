// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// Polar.h - definition of 2D polar coordinate class

#ifndef _POLAR_H_
#define _POLAR_H_

#include <string>
#include "Coordinate.h"

using namespace std;

class Polar : public Coordinate{
 public:
  // Construct the polar coordinate (r, a)
  Polar(double, double);

  // return a string representation
  virtual string ToString() const;

  // return the distance between the object and a second Polar point object
  double Distance(const Polar&) const;

 private:
  double r_;  // radius
  double a_;  // angle
};

#endif  // _POLAR_H_
