// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// Header file for Vector.cc
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

namespace vector333 {

class Vector {
 public:
  Vector();  // default constructor
  // overloaded Constructor
  Vector(const float x, const float y, const float z);
  Vector(const Vector& v);  // copy constructor
  ~Vector();  // Destructor

  // Override the "=", "+=", "-=" and "*" operators.
  Vector& operator=(const Vector &v);
  Vector& operator+=(const Vector &v);
  Vector& operator-=(const Vector &v);
  double operator*(const Vector &v);
  Vector operator*(const double k);
  friend std::ostream &operator<<(std::ostream &out, const Vector &v);

 private:  // private instance variables
  float x_, y_, z_;  // Member variables.
};

Vector operator+(const Vector &v1, const Vector &v2);
Vector operator-(const Vector &v1, const Vector &v2);
Vector operator*(double k, const Vector &v);

}  // namespace vector333

#endif  // _VECTOR_H_
