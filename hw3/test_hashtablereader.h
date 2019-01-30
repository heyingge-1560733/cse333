/*
 * Copyright ©2018 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#ifndef _HW3_TEST_HASHTABLEREADER_H_
#define _HW3_TEST_HASHTABLEREADER_H_

#include <unistd.h>
#include <iostream>
#include "gtest/gtest.h"

#include "./HashTableReader.h"

namespace hw3 {

class Test_HashTableReader : public ::testing::Test {
 protected:
  Test_HashTableReader() {
    // Do set-up work for each test here.
  }

  virtual ~Test_HashTableReader() {
    // Do clean-up work for each test here.
  }

  virtual void SetUp() {
    // Code here will be called after the constructor and
    // right before each test.
  }

  virtual void TearDown() {
    // Code here will be called after each test and
    // right before the destructor.
  }

  static void SetUpTestCase() {
    // Code here will be called once for the entire
    // text fixture.  Note it is a static member function
    // (i.e., a class method, not an object instance method).
  }

  static void TearDownTestCase() {
    // Code here will be called once for the entire
    // text fixture.  Note it is a static member function
    // (i.e., a class method, not an object instance method).
  }

  // These are accessor methods that return protected member
  // variables of HashTableReader.
  IndexFileOffset_t get_offset(HashTableReader *htr) {
    return htr->offset_;
  }

  HWSize_t get_num_buckets(HashTableReader *htr) {
    return htr->header_.num_buckets;
  }

  // Objects declared here can be used by all tests in
  // the test case.
};  // class Test_HashTableReader

}  // namespace hw3

#endif  // _HW3_TEST_HASHTABLEREADER_H_
