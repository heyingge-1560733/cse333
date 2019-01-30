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

#ifndef _HW3_DOCIDTABLEREADER_H_
#define _HW3_DOCIDTABLEREADER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <list>      // for std::list
#include <utility>   // for std::pair
#include <cstdio>    // for (FILE *)

#include "./HashTableChecker.h"

using std::list;
using std::pair;

namespace hw3 {

// A DocIDTableChecker (a subclass of HashTableChecker) is used to
// read one of the many the embedded docid-->positions "docIDtable"
// tables within the index file.
class DocIDTableChecker : public HashTableChecker {
 public:
  // Construct a new DocIDTableChecker at a specific offset with an
  // index file.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed object takes ownership of the (FILE *) and will
  //   fclose() it  on destruction.
  //
  // - offset: the "docIDtable"'s byte offset within the file.
   DocIDTableChecker(FILE *f, uint32_t offset, uint32_t len);
  ~DocIDTableChecker() { }

  // Check a DocIDTableElement.
  virtual void CheckElement(uint32_t element_offset,
                            uint32_t bucket_number);

};

}  // namespace hw3

#endif  // _HW3_DOCIDTABLEREADER_H_
