// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// Cartesian.cc - implementation of class Cartesian

#include <math.h>
#include <string>
#include "Cartesian.h"

using namespace std;

// constructor
Cartesian::Cartesian(double x, double y) : x_(x), y_(y) {}

string Cartesian::ToString() const {
  return "(" + to_string(x_) + ", " + to_string(y_) + ") in cartesian form";
}

double Cartesian::Distance(const Cartesian &c) const {
  return sqrt(pow(x_ - c.x_, 2.0) + pow(y_ - c.y_, 2.0));
}

