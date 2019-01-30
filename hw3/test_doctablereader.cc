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

#include <cstdio>

#include "./filelayout.h"
#include "./fileindexutil.h"
#include "./test_doctablereader.h"
#include "./test_suite.h"

extern "C" {
#include "libhw1/HashTable.h"
}

namespace hw3 {

TEST_F(Test_DocTableReader, TestDocTableReaderBasic) {
  // Open up the FILE * for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(nullptr), f);

  // Prep the DocTableReader; the docid-->docname table is at
  // offset sizeof(IndexFileHeader).
  DocTableReader dtr(f, sizeof(IndexFileHeader));

  // Do a couple of bucket lookups, just to make sure we're
  // inheriting LookupElementPositions correctly.
  auto res = LookupElementPositions(&dtr, 5);
  ASSERT_GT(res.size(), (unsigned int) 0);

  res = LookupElementPositions(&dtr, 6);
  ASSERT_GT(res.size(), (unsigned int) 0);

  // Try some docid-->string lookups.  Start by trying two that
  // should exist.
  std::string str;
  bool success = dtr.LookupDocID(5, &str);
  ASSERT_TRUE(success);
  ASSERT_EQ(std::string("test_tree/enron_email/102."),
            str);
  success = dtr.LookupDocID(55, &str);
  ASSERT_TRUE(success);
  ASSERT_EQ(std::string("test_tree/enron_email/149."),
            str);

  // Lookup a docid that shouldn't exist.
  success = dtr.LookupDocID(100000, &str);
  ASSERT_FALSE(success);

  // Done!
  HW3Addpoints(30);
}

}  // namespace hw3
