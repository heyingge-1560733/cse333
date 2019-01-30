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

#include <assert.h>     // for assert()
#include <arpa/inet.h>  // for ntohl(), etc.
#include <stdint.h>     // for uint32_t, etc.
#include <iostream>     // for cout, endl, etc.

#include "./fileindexutil.h"  // for ntohll()

#include "./DocIDTableChecker.h"

using namespace std;

namespace hw3 {

// The constructor for DocIDTableChecker calls the constructor
// of HashTableChecker(), its superclass. The superclass takes
// care of taking ownership of f and using it to extract and
// cache the number of buckets within the table.
DocIDTableChecker::DocIDTableChecker(FILE *f, uint32_t offset, uint32_t len)
  : HashTableChecker(f, offset, len) { }

void DocIDTableChecker::CheckElement(uint32_t element_offset,
                                     uint32_t bucket_number) {
  // seek to the start of the element
  assert(fseek(file_, element_offset, SEEK_SET) == 0);

  // read the docID
  uint64_t docid;
  assert(fread(&docid, 8, 1, file_) == 1);
  docid = ntohll(docid);

  // make sure the docID is in the right bucket
  Check64(bucket_number, (uint32_t) (docid % num_buckets_),
          "[DocID table] DocID % num_buckets == bucket_number");

  // read in the number of positions
  uint32_t numposn;
  assert(fread(&numposn, 4, 1, file_) == 1);
  numposn = ntohl(numposn);
  CheckLT32(numposn, 1000000, "[DocID table] num_positions");

  // loop through and check the positions
  uint32_t prevposn;
  for (uint32_t i = 0; i < numposn; i++) {
    uint32_t curposn;
    assert(fread(&curposn, 4, 1, file_) == 1);
    curposn = ntohl(curposn);
    if (i > 0) {
      CheckLT32(prevposn,
                curposn,
                "word position[i] < word position[i+1]");
    }
    prevposn = curposn;
  }
}

}  // namespace hw3
