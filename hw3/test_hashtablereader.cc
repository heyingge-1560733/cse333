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
#include "./test_hashtablereader.h"
#include "./test_suite.h"

namespace hw3 {

TEST_F(Test_HashTableReader, TestHashTableReaderBasic) {
  // Open up the FILE * for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(nullptr), f);

  // Prep the HashTableReader to point to the docid-->docname table,
  // which is at offset sizeof(IndexFileHeader) in the file.
  HashTableReader htr(f, sizeof(IndexFileHeader));

  // Do a couple of bucket lookups.
  auto res = htr.LookupElementPositions(5);
  ASSERT_GT(res.size(), (unsigned int) 0);

  res = htr.LookupElementPositions(6);
  ASSERT_GT(res.size(), (unsigned int) 0);

  // Done!
  HW3Addpoints(20);
}

}  // namespace hw3
