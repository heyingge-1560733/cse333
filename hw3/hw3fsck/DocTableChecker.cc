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
#include <sstream>      // for std::stringstream
#include <iostream>     // for cout
#include <cctype>       // for isascii

#include "./fileindexutil.h"  // for ntohll()

#include "./DocTableChecker.h"

namespace hw3 {

// The constructor for DocTableChecker calls the constructor
// of HashTableReader(), its superclass. The superclass takes
// care of taking ownership of f and using it to extract and
// cache the number of buckets within the table.
DocTableChecker::DocTableChecker(FILE *f, uint32_t offset, uint32_t len)
  : HashTableChecker(f, offset, len) { }

void DocTableChecker::CheckElement(uint32_t element_offset,
                                   uint32_t bucket_number) {
  // Read in the docID
  uint64_t docID;
  assert(fseek(file_, element_offset, SEEK_SET) == 0);
  assert(fread(&docID, 8, 1, file_) == 1);
  docID = ntohll(docID);

  // Make sure the docID makes sense for this bucket.
  Check32(bucket_number, (uint32_t) (docID % num_buckets_),
          "[DocTable] DocID % num_buckets_ == bucket_number");

  // Read in the filename length.
  uint16_t fnlen;
  assert(fread(&fnlen, 2, 1, file_) == 1);
  fnlen = ntohs(fnlen);
  CheckLT16(fnlen, 1024, "[DocTable] filename length");

  // Read in the filename.
  char filename[fnlen+1];
  filename[fnlen] = '\0';
  assert(fread(&filename[0], fnlen, 1, file_) == 1);

  // Make sure the filename is all ASCII.
  for (int i = 0; i < fnlen; i++) {
    uint16_t res = isascii(filename[i]) ? 1 : 0;
    Check16(1, res,
            string(("[DocTable] isascii(filename)[" +
                    to_string(i) + "]")).c_str());
  }
}

}  // namespace hw3
