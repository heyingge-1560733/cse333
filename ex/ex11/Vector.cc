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
 * Vector.cc - implementation of class Vector
 */

#include <iostream>
using namespace std;

#include "./Vector.h"

namespace vector333 {

// constructors:

Vector::Vector() {
  arr_ = new float[3];  // dynamically allocate an array with 3 floats
  arr_[0] = arr_[1] = arr_[2] = 0.0;
}

Vector::Vector(const float x, const float y, const float z) {
  arr_ = new float[3];  // dynamically allocate an array with 3 floats
  arr_[0] = x;
  arr_[1] = y;
  arr_[2] = z;
}

// Copy constructor
Vector::Vector(const Vector &v) {
  arr_ = new float[3];  // dynamically allocate an array with 3 floats
  arr_[0] = v.arr_[0];
  arr_[1] = v.arr_[1];
  arr_[2] = v.arr_[2];
}

// Destructor
Vector::~Vector() {
  delete[] arr_;  // deallocate the array
}

// Vector assignment
Vector &Vector::operator=(const Vector &rhs) {
  // replace state of this with values from rhs; do nothing if
  // self-asignment. (Even though in this particular case there would
  // be no harm, it's always best to check for self-assignment and do
  // nothing if detected.)
  if (this != &rhs) {
    arr_[0] = rhs.arr_[0];
    arr_[1] = rhs.arr_[1];
    arr_[2] = rhs.arr_[2];
  }
  // return reference to lhs of assignment
  return *this;
}

// Updating assignments for vectors

Vector &Vector::operator+=(const Vector &rhs) {
  arr_[0] += rhs.arr_[0];
  arr_[1] += rhs.arr_[1];
  arr_[2] += rhs.arr_[2];
  return *this;
}

Vector &Vector::operator-=(const Vector &rhs) {
  arr_[0] -= rhs.arr_[0];
  arr_[1] -= rhs.arr_[1];
  arr_[2] -= rhs.arr_[2];
  return *this;
}

// Friend functions that are not members of class Vector

// dot-product: if a is (a,b,c) and b is (x,y,z),
// return ax+by+cz
double operator*(const Vector &a, const Vector &b) {
  return a.arr_[0]*b.arr_[0] + a.arr_[1]*b.arr_[1] + a.arr_[2]*b.arr_[2];
}

// scalar multiplication: if v is (a,b,c), return (ak,bk,ck)
Vector operator*(const double k, const Vector &v) {
  return Vector(v.arr_[0] * k, v.arr_[1] * k, v.arr_[2] * k);
}
Vector operator*(const Vector &v, const double k) {
  return Vector(v.arr_[0] * k, v.arr_[1] * k, v.arr_[2] * k);
}

// Stream output: << for Vectors
ostream & operator<<(ostream &out, const Vector &v) {
  out << "(" << v.arr_[0] << "," << v.arr_[1] << "," << v.arr_[2] << ")";
  return out;
}

// Additional non-member functions that are part of the Vector absraction

// Vector addition
Vector operator+(const Vector &a, const Vector &b) {
  Vector tmp = a;
  tmp += b;
  return tmp;
}

// Vector subtraction
Vector operator-(const Vector &a, const Vector &b) {
  Vector tmp = a;
  tmp -= b;
  return tmp;
}

}  // namespace vector333
