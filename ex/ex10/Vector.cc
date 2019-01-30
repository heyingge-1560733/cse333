// 1560733
// heyingge@uw.edu
// "Copyright [2018] <Yingge He>"  [legal/copyright]
// This program inplements the Vector class.
#include "Vector.h"
#include <iostream>
#include <sstream>
#include <string>


namespace vector333 {

Vector::Vector() : x_(0), y_(0), z_(0) { }

Vector::Vector(const float x, const float y, const float z) :
        x_(x), y_(y), z_(z) { }

Vector::Vector(const Vector &copyme) {
  x_ = copyme.x_;
  y_ = copyme.y_;
  z_ = copyme.z_;
}

Vector::~Vector() { }

Vector &Vector::operator=(const Vector &v) {
  if (this != &v) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = v.z_;
  }
  return *this;
}

Vector &Vector::operator+=(const Vector &v) {
  x_ += v.x_;
  y_ += v.y_;
  z_ += v.z_;
  return *this;
}

Vector &Vector::operator-=(const Vector &v) {
  x_ -= v.x_;
  y_ -= v.y_;
  z_ -= v.z_;
  return *this;
}

Vector operator+(const Vector &v1, const Vector &v2) {
  Vector tmp;
  tmp = v1;
  tmp += v2;
  return tmp;
}

Vector operator-(const Vector &v1, const Vector &v2) {
  Vector tmp;
  tmp = v1;
  tmp -= v2;
  return tmp;
}

double Vector::operator*(const Vector &v) {
  return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

Vector Vector::operator*(const double k) {
  Vector tmp((float)(x_ * k), (float)(y_ * k), (float)(z_ * k));
  return tmp;
}

Vector operator*(double k, const Vector &v) {
  Vector tmp;
  tmp = v;
  return tmp * k;
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
  out << "(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
  return out;
}

}  // namespace vector333
