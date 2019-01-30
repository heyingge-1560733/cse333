// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// Polar.cc - implementation of class Polar

#include <math.h>
#include "Polar.h"

#define PI 3.14159265

// constructor
Polar::Polar(double r, double a) : r_(r), a_(a) {}

string Polar::ToString() const {
  return "(" + to_string(r_) + ", " + to_string(a_) + ") in polar form";
}

double Polar::Distance(const Polar &p) const {
  return sqrt(pow(r_, 2.0) + pow(p.r_, 2.0) -
              2 * r_ * p.r_ * cos((a_ - p.a_) * PI / 180));
}
