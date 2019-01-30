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
#include "./test_indextablereader.h"
#include "./test_suite.h"

extern "C" {
  #include "libhw1/HashTable.h"
  #include "libhw1/CSE333.h"
}

namespace hw3 {

TEST_F(Test_IndexTableReader, TestIndexTableReaderBasic) {
  // Open up the (FILE *) for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(nullptr), f);

  // Read in the size of the doctable.
  Verify333(fseek(f, DTSIZE_OFFSET, SEEK_SET) == 0);
  HWSize_t doctable_size;
  Verify333(fread(&doctable_size, 4, 1, f) == 1);
  doctable_size = ntohl(doctable_size);

  // Prep the IndexTableReader; the word-->docid_table table is at
  // offset sizeof(IndexFileHeader) + doctable_size.
  IndexTableReader itr(f, sizeof(IndexFileHeader) + doctable_size);

  // Do a couple of bucket lookups, just to make sure we're
  // inheriting LookupElementPositions correctly.
  HTKey_t h1 = FNVHash64((unsigned char *) "anyway", 6);
  auto res = LookupElementPositions(&itr, h1);
  ASSERT_GT(res.size(), (unsigned int) 0);

  HTKey_t h2 = FNVHash64((unsigned char *) "attachment", 10);
  res = LookupElementPositions(&itr, h2);
  ASSERT_GT(res.size(), (unsigned int) 0);

  // The unit test test_docidtablereader.cc exercises the
  // IndexTableReader's LookupWord() method, so we won't replicate that
  // here.
  //
  // Done!
  HW3Addpoints(30);
}

}  // namespace hw3
