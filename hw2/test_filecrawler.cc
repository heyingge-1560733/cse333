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

#include <stdio.h>
#include <stdlib.h>

extern "C" {
  #include "./filecrawler.h"
  #include "./doctable.h"
  #include "./memindex.h"
}

#include "./test_suite.h"
#include "./test_filecrawler.h"

namespace hw2 {

TEST_F(Test_FileCrawler, FCTestSimple) {
  int res;
  DocTable dt;
  MemIndex idx;

  res = CrawlFileTree(const_cast<char *>("./test_tree/bash-4.2/support"),
                      &dt,
                      &idx);
  ASSERT_EQ(1, res);
  HW2Addpoints(10);
  FreeDocTable(dt);
  FreeMemIndex(idx);
  HW2Addpoints(10);

  res = CrawlFileTree(const_cast<char *>("./nonexistent/"), &dt, &idx);
  ASSERT_EQ(0, res);
  HW2Addpoints(10);
  res = CrawlFileTree(const_cast<char *>("./test_suite.c"), &dt, &idx);
  ASSERT_EQ(0, res);
  HW2Addpoints(10);
}

}  // namespace hw2

