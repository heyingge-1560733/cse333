// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// Header file for IntPair.cc

#ifndef _INTPAIR_H_
#define _INTPAIR_H_

// This class stores a pair of integers.
class IntPair {
 public:
  // construct a new IntPair with the two integers being x and y
  IntPair(const int x, const int y);

  // returns the two integers through output parameters
  void Get(int *x_ptr, int *y_ptr) const;

  // reassign the two integers to be x and y
  void Set(int x, int y);

 private:
  // private instance variables
  int x_;
  int y_;
};

#endif
