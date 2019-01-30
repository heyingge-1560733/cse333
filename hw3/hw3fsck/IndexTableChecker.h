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

#ifndef _HW3_INDEXTABLECHECKER_H_
#define _HW3_INDEXTABLECHECKER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string.
#include <cstdio>    // for (FILE *)

#include "./HashTableChecker.h"
#include "./DocIDTableChecker.h"

namespace hw3 {

// An IndexTableChecker is a subclass of HashTableChecker used to
// read the word-->docID_table "index" within the index file.
class IndexTableChecker : public HashTableChecker {
 public:
  // Construct an IndexTableChecker.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The new
  //   object takes ownership of the (FILE *) and will fclose() it
  //   on destruction.
  //
  // - offset: the file offset of the first byte of the doctable
   IndexTableChecker(FILE *f, uint32_t offset, uint32_t len);
  ~IndexTableChecker() { }

  // Check an IndexTableElement.
  virtual void CheckElement(uint32_t element_offset,
                            uint32_t bucket_number);
};

}  // namespace hw3

#endif  // _HW3_INDEXTABLECHECKER_H_
