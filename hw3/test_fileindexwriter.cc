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

#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>

#include "./test_fileindexwriter.h"
#include "./fileindexwriter.h"
#include "./test_suite.h"

namespace hw3 {

// Test our ability to write to a file index.
TEST_F(Test_FileIndexWriter, TestFileIndexWrite) {
  uint32_t mypid = (uint32_t) getpid();
  std::stringstream ss;
  ss << "/tmp/test." << mypid << ".index";
  std::string fname = ss.str();

  std::cout << "             " <<
    "Writing index " << mi_ << "out to " << fname << "..." << std::endl;
  HWSize_t res = WriteIndex(mi_, dt_, fname.c_str());
  std::cout << "             " <<
    "...done writing." << std::endl;
  ASSERT_EQ(unlink(fname.c_str()), 0);
  ASSERT_LT((HWSize_t) 100000, res);

  HW3Addpoints(20);
}

}  // namespace hw3
