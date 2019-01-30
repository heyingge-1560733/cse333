// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// Coordinate.h - definition of 2D coordinate class

#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <string>

using namespace std;

class Coordinate {
 public:
  // return a string representation
  virtual string ToString() const = 0;
};

#endif  // _COORDINATE_H_
