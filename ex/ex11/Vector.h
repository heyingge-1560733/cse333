/*
 * Yingge He
 * 1560733
 * heyingge@uw.edu
 *
 * Copied from sample solution from ex10.
 * Copyright ©2018 Justin Hsia, Yingge He.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

/* 
 * Vector.h - definition of 3D vector class
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
using namespace std;

namespace vector333 {

// A Vector represents a vector in 3-space.
class Vector {
 public:
  // constructors:

  // Default: construct the vector (0,0,0)
  Vector();

  // Construct the vector (x,y,z)
  Vector(const float x, const float y, const float z);

  // Copy constructor
  Vector(const Vector &v);

  // Destructor
  ~Vector();

  // Assignment
  Vector &operator=(const Vector &rhs);

  // Updating assignment
  Vector &operator+=(const Vector &rhs);
  Vector &operator-=(const Vector &rhs);

  // Additional functions that are not members of Vector but
  // need to be friends so they can access instance variables:

  // dot-product: if a is (a,b,c) and b is (x,y,z),
  // return ax+by+cz
  // (note: ok if result is float; specification wasn't specific)
  friend double operator*(const Vector &a, const Vector &b);

  // scalar multiplication: if v is (a,b,c), return (ak,bk,ck)
  friend Vector operator*(const double k, const Vector &v);
  friend Vector operator*(const Vector &v, const double k);

  // Stream output: define << for Vectors
  friend ostream & operator<<(ostream &out, const Vector &v);

 private:
  // The representation of a Vector is an array with three floats
  // giving the x, y, and z magnitudes.
  float* arr_;
};

// additional operations that are not members or friend functions but
// are part of the Vector abstraction

// addition and subtraction: produce a new Vector that results from
// element-wise addition or subtraction of this with other
Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);

}  // namespace vector333

#endif  //  _VECTOR_H_
