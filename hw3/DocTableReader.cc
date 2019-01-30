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

#include <stdint.h>     // for uint32_t, etc.
#include <sstream>      // for std::stringstream

#include "./DocTableReader.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw3 {

// The constructor for DocTableReader calls the constructor
// of HashTableReader(), its superclass. The superclass takes
// care of taking ownership of f and using it to extract and
// cache the number of buckets within the table.
DocTableReader::DocTableReader(FILE *f, IndexFileOffset_t offset)
  : HashTableReader(f, offset) { }

bool DocTableReader::LookupDocID(const DocID_t &docid,
                                 std::string *ret_str) {
  // Use the superclass's "LookupElementPositions" function to
  // walk through the doctable and get back a list of offsets
  // to elements in the bucket for this docID.
  auto elements = LookupElementPositions(docid);

  // If the list is empty, we're done.
  if (elements.size() == 0)
    return false;

  // Iterate through the elements, looking for our docID.
  for (auto it = elements.begin(); it != elements.end(); it++) {
    IndexFileOffset_t next_offset = *it;

    // Slurp the next docid out of the element.
    doctable_element_header header;
    // MISSING:
    Verify333(fseek(file_, next_offset, SEEK_SET) == 0);
    Verify333(fread(&header, sizeof(header), 1, file_) == 1);
    header.toHostFormat();

    // Is it a match?
    if (header.docid == docid) {
      // Yes!  Extract the filename, using a stringstream and its "<<"
      // operator, fread()'ing a character at a time.
      std::stringstream ss;
      for (int i = 0; i < header.filename_len; i++) {
        uint8_t nextc;

        Verify333(fread(&nextc, 1, 1, file_) == 1);
        ss << nextc;
      }

      // Using the str() method of ss to extract a std::string object,
      // and return it through the output parameter ret_str.  Return
      // true.
      // MISSING:
      *ret_str = ss.str();

      return true;
    }
  }

  // We failed to find a matching docID, so return false.
  return false;
}

}  // namespace hw3
