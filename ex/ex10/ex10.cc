// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program tests the functionality of the class Vector.
#include <iostream>
#include "Vector.h"

using namespace vector333;
using namespace std;
int main(int argc, char **argv) {
  // test constructing vectors
  Vector a, b(0, 1, 2), c(-3, -4, -5);
  cout << "Vector a: " << a << "    Expected: (0,0,0)" << endl;
  cout << "Vector b: " << b << "    Expected: (0,1,2)" << endl;
  cout << "Vector b: " << c << "    Expected: (-3,-4,-5)" << endl << endl;

  // test "=" operator
  Vector acopy(a), bcopy(b), ccopy(c);
  cout << "Copy of Vector a: " << acopy << "    Expected: (0,0,0)" << endl;
  cout << "Copy of Vector b: " << bcopy << "    Expected: (0,1,2)" << endl;
  cout << "Copy of Vector b: " << ccopy <<
  "    Expected: (-3,-4,-5)" << endl << endl;

  // test "+" operator
  Vector aplusb = a + b;
  Vector aplusc = a + c;
  Vector bplusc = b + c;
  cout << "Vector a + b: " << aplusb << "    Expected: (0,1,2)" << endl;
  cout << "Vector a + c: " << aplusc << "    Expected: (-3,-4,-5)" << endl;
  cout << "Vector b + c: " << bplusc <<
  "    Expected: (-3,-3,-3)" << endl << endl;

  // test "-" operator
  Vector aminusb = a - b;
  Vector aminusc = a - c;
  Vector bminusc = b - c;
  cout << "Vector a - b: " << aminusb << "    Expected: (0,-1,-2)" << endl;
  cout << "Vector a - c: " << aminusc << "    Expected: (3,4,5)" << endl;
  cout << "Vector b - c: " << bminusc <<
  "    Expected: (3,5,7)" << endl << endl;

  // test inner product of two Vectors
  double amultb = a * b;
  double amultc = a * c;
  double bmultc = b * c;
  cout << "Vector a * b: " << amultb << "    Expected: 0" << endl;
  cout << "Vector a * c: " << amultc << "    Expected: -0" << endl;
  cout << "Vector b * c: " << bmultc << "    Expected: -14" << endl << endl;

  // test scaler product of two Vectors
  Vector amultk = a * 2.0;
  Vector bmultk = -0.1 * b;
  Vector cmultk = c * 1.5;
  cout << "Vector a * 2.0: " << amultk << "    Expected: (0,0,0)" << endl;
  cout << "Vector -0.1 * b: " << bmultk <<
  "    Expected: (-0,-0.1,-0.2)" << endl;
  cout << "Vector c * 1.5: " << cmultk <<
  "    Expected: (-4.5,-6,-7.5)" << endl << endl;

  // test "-=" operator
  Vector m, n, o;
  m -= a;
  n -= b;
  o -= c;
  cout << "Vector m: " << m << "    Expected: (0,0,0)" << endl;
  cout << "Vector n: " << n << "    Expected: (0,-1,-2)" << endl;
  cout << "Vector o: " << o << "    Expected: (3,4,5)" << endl << endl;

  // test "+=" operator
  m += a;
  n += b;
  o += c;
  cout << "Vector m: " << m << "    Expected: (0,0,0)" << endl;
  cout << "Vector n: " << n << "    Expected: (0,0,0)" << endl;
  cout << "Vector o: " << o << "    Expected: (0,0,0)" << endl << endl;

  // test "=" operator
  m = a;
  n = b;
  o = c;

  cout << "Vector m: " << m << "    Expected: (0,0,0)" << endl;
  cout << "Vector n: " << n << "    Expected: (0,1,2)" << endl;
  cout << "Vector o: " << o << "    Expected: (-3,-4,-5)" << endl << endl;

  return 0;  // success
}

