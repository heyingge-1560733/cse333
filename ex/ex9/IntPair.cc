// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program inplements IntPair class.

#include "IntPair.h"

IntPair::IntPair(const int x, const int y) : x_(x), y_(y) { }

void IntPair::Get(int *x_ptr, int *y_ptr) const {
  *x_ptr = x_;
  *y_ptr = y_;
}

void IntPair::Set(int x, int y) {
  x_ = x;
  y_ = y;
}
