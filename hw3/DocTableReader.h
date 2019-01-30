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

#ifndef _HW3_DOCTABLEREADER_H_
#define _HW3_DOCTABLEREADER_H_

#include <string>    // for std::string
#include <cstdio>    // for (FILE *)

#include "./HashTableReader.h"

namespace hw3 {

// A DocTableReader (a subclass of HashTableReader) is used to
// read the single docid-->docname "doctable" within the index file.
class DocTableReader : protected HashTableReader {
  // This friend declaration is here so that the Test_DocTableReader
  // unit test fixture can access protected member variables of
  // DocTableReader.  See test_doctablereader.h for details.
  friend class Test_DocTableReader;

  // Similarly, the debug printing method needs access to objects
  // of this class.
  friend void dumpFileIndex(const char*);

 public:
  // Construct a new DocTableReader at a specified offset within
  // an index file.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed  object takes ownership of the (FILE *) and will
  //   fclose() it on destruction.
  //
  // - offset: the "doctable"'s byte offset within the file.
  DocTableReader(FILE *f, IndexFileOffset_t offset);
  ~DocTableReader() { }

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
  bool LookupDocID(const DocID_t &docid, std::string *ret_str);
};

}  // namespace hw3

#endif  // _HW3_DOCTABLEREADER_H_
