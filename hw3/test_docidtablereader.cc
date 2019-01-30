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
#include <iostream>
#include <algorithm>

#include "./filelayout.h"
#include "./fileindexutil.h"
#include "./IndexTableReader.h"
#include "./test_docidtablereader.h"
#include "./test_suite.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw3 {

TEST_F(Test_DocIDTableReader, TestDocIDTableReaderBasic) {
  // This is a tough unit test to write, since we can't assume
  // much about where in an index file a DocIDTable lives.
  // So, we violate a little bit of the unit testing credo and
  // fold in a different module as a dependency: we make use of the
  // IndexTableReader class.

  // Open up the FILE * for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FILE *f = fopen(idx.c_str(), "rb");
  ASSERT_NE(static_cast<FILE *>(nullptr), f);

  // Read in the size of the doctable.
  Verify333(fseek(f, DTSIZE_OFFSET, SEEK_SET) == 0);
  HWSize_t doctable_size;
  Verify333(fread(&doctable_size, 4, 1, f) == 1);
  doctable_size = ntohl(doctable_size);

  // Prep an IndexTableReader; the word-->docid table is at offset
  // sizeof(IndexFileHeader) + doctable_size
  IndexTableReader itr(f, sizeof(IndexFileHeader) + doctable_size);

  // Use the IndexTableReader to manufacture a DocIDTableReader.
  DocIDTableReader *ditr = itr.LookupWord(std::string("happy"));
  ASSERT_NE(static_cast<DocIDTableReader *>(nullptr), ditr);

  // Use the DocIDTableReader to look for matching docids.
  std::list<DocPositionOffset_t> matchlist;
  bool success = ditr->LookupDocID(604, &matchlist);
  ASSERT_TRUE(success);
  ASSERT_EQ((unsigned int) 2, matchlist.size());

  matchlist.clear();
  success = ditr->LookupDocID(613, &matchlist);
  ASSERT_TRUE(success);
  ASSERT_EQ((unsigned int) 1, matchlist.size());

  matchlist.clear();
  success = ditr->LookupDocID(37, &matchlist);
  ASSERT_TRUE(success);
  ASSERT_EQ((unsigned int) 1, matchlist.size());

  // Lookup a docID that shouldn't exist.
  matchlist.clear();
  success = ditr->LookupDocID(100000, &matchlist);
  ASSERT_FALSE(success);
  ASSERT_EQ((unsigned int) 0, matchlist.size());

  // Clean up.
  delete ditr;

  // Done!
  HW3Addpoints(30);
}

}  // namespace hw3
