// Yingge He
// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program tests the functionality of Cartesian class and Polar class.

#include <iostream>
#include "Cartesian.h"
#include "Polar.h"

using namespace std;

int main(int argc, char **argv) {
  Cartesian c1(3.0, 0);  // c1(3, 0)
  Cartesian c2(0, -4.0);  // c2(0, -4)
  cout << "C1: " << c1.ToString() << endl;
  cout << "C2: " << c2.ToString() << endl;
  cout << "The distance between c1 and c2 is " << c1.Distance(c2) << endl;
  cout << endl;

  Polar p1(3.0, 0);  // p1(3, 0)
  Polar p2(4.0, 270.0);  // p2(4, 270)
  cout << "P1: " << p1.ToString() << endl;
  cout << "P2: " << p2.ToString() << endl;
  cout << "The distance between p1 and p2 is " << p1.Distance(p2) << endl;

  return EXIT_SUCCESS;  // success
}
