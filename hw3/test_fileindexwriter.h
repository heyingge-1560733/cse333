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

#ifndef _HW3_TEST_FILEINDEXWRITER_H_
#define _HW3_TEST_FILEINDEXWRITER_H_

#include <iostream>
#include "gtest/gtest.h"

extern "C" {
#include "libhw2/filecrawler.h"
#include "libhw2/doctable.h"
#include "libhw2/memindex.h"
}

namespace hw3 {

class Test_FileIndexWriter : public ::testing::Test {
 protected:
  Test_FileIndexWriter() {
    // Do set-up work for each test here.
  }

  virtual ~Test_FileIndexWriter() {
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
    int res;
    std::cout << "             Crawling ./test_tree/enron_mail..."
              << std::endl;
    res = CrawlFileTree(const_cast<char *>("./test_tree/enron_email"),
                        &Test_FileIndexWriter::dt_,
                        &Test_FileIndexWriter::mi_);
    std::cout << "               ...done crawling." << std::endl;
    ASSERT_NE(0, res);
  }

  static void TearDownTestCase() {
    // Code here will be called once for the entire
    // text fixture.  Note it is a static member function
    // (i.e., a class method, not an object instance method).
    FreeDocTable(dt_);
    FreeMemIndex(mi_);
    dt_ = nullptr;
    mi_ = nullptr;
  }

  // Objects declared here can be used by all tests in
  // the test case.

  // We'll reuse the MemIndex and DocTable across tests.
  static DocTable dt_;
  static MemIndex mi_;
};  // class Test_FileIndexWriter

DocTable Test_FileIndexWriter::dt_;
MemIndex Test_FileIndexWriter::mi_;

}  // namespace hw3

#endif  // _HW3_TEST_FILEINDEXWRITER_H_
