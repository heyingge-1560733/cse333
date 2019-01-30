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

#ifndef _HW3_TEST_INDEXTABLEREADER_H_
#define _HW3_TEST_INDEXTABLEREADER_H_

#include <unistd.h>
#include <iostream>
#include <list>
#include "gtest/gtest.h"

#include "./IndexTableReader.h"
#include "./fileindexwriter.h"

namespace hw3 {

class Test_IndexTableReader : public ::testing::Test {
 protected:
  Test_IndexTableReader() {
    // Do set-up work for each test here.
  }

  virtual ~Test_IndexTableReader() {
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

  // These relay is so that the unit test can access the
  // protected member functions of IndexTableReader.
  std::list<IndexFileOffset_t> LookupElementPositions(IndexTableReader *itr,
                                             HTKey_t hashval) {
    return itr->LookupElementPositions(hashval);
  }

  // Objects declared here can be used by all tests in
  // the test case.
};  // class Test_IndexTableReader

}  // namespace hw3

#endif  // _HW3_TEST_INDEXTABLEREADER_H_
