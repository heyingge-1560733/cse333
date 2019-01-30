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

#ifndef _HW3_TEST_FILEINDEXREADER_H_
#define _HW3_TEST_FILEINDEXREADER_H_

#include <unistd.h>
#include <iostream>
#include "gtest/gtest.h"

#include "./FileIndexReader.h"

namespace hw3 {

class Test_FileIndexReader : public ::testing::Test {
 protected:
  Test_FileIndexReader() {
    // Do set-up work for each test here.
  }

  virtual ~Test_FileIndexReader() {
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
  // variables of FileIndexReader.
  HWSize_t get_doctable_size(FileIndexReader *fir) {
    return fir->header_.doctable_size;
  }

  HWSize_t get_index_size(FileIndexReader *fir) {
    return fir->header_.index_size;
  }

  // Objects declared here can be used by all tests in
  // the test case.
};  // class Test_FileIndexReader

}  // namespace hw3

#endif  // _HW3_TEST_FILEINDEXREADER_H_
