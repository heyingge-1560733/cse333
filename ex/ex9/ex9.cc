// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program tests whether or not class instances are passed by
// value or passed by reference. The result outputs to stdout.

#include <iostream>
#include <cstdlib>
#include "IntPair.h"

using namespace std;

void Test(IntPair ip) {
  int x, y;
  ip.Get(&x, &y);  // get the current value of the integers in IntPair
  ip.Set(x+1, y+1);  // increment the value of the integers in IntPair by 1
}

int main() {
  const int old_x = 0;  // initialize x
  const int old_y = 1;  // initialize y
  IntPair ip(old_x, old_y);  // initialize a IntPair
  Test(ip);

  int new_x, new_y;
  ip.Get(&new_x, &new_y);  // get the new values of x and y

  if (old_x != new_x || old_y != new_y)  // value of x or y changes
    cout << "Is pass by reference" << endl;
  else  // values of x and y are not changed
    cout << "Is pass by value" << endl;

  return EXIT_SUCCESS;  // success
}
