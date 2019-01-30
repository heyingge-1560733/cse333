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

#ifndef _HW3_DOCTABLECHECKER_H_
#define _HW3_DOCTABLECHECKER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string
#include <cstdio>    // for (FILE *)

#include "./HashTableChecker.h"

namespace hw3 {

// A DocTableChecker (a subclass of HashTableChecker) is used to
// read the single docid-->docname "doctable" within the index file.
class DocTableChecker : public HashTableChecker {
 public:
  // Construct a new DocTableChecker at a specified offset within
  // an index file.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed  object takes ownership of the (FILE *) and will
  //   fclose() it on destruction.
  //
  // - offset: the "doctable"'s byte offset within the file.
   DocTableChecker(FILE *f, uint32_t offset, uint32_t len);
  ~DocTableChecker() { }

  // Check a DocTableElement.
  virtual void CheckElement(uint32_t element_offset,
                            uint32_t bucket_number);

  // Lookup a docid and get back a std::string containing the filename
  // associated with the docid, if it exists.
  //
  // Arguments:
  //
  // - docid:  the docID to look for within the doctable.
  //
  // - ret_tr: the string containing the filename (an output parameter).
  //   Nothing is returned through this if the docID is not found.
  //
  // Returns:
  //
  // - true if the docID is found, false otherwise.
  // bool LookupDocID(const uint64_t &docid, std::string *ret_str);
};

}  // namespace hw3

#endif  // _HW3_DOCTABLECHECKER_H_
