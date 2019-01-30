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

#ifndef _HW3_FILEINDEXREADER_H_
#define _HW3_FILEINDEXREADER_H_

#include <string>    // for std::string
#include <cstdio>    // for (FILE *)

#include "./filelayout.h"
#include "./fileindexutil.h"    // for DISALLOW_COPY_AND_ASSIGN()
#include "./DocTableReader.h"
#include "./IndexTableReader.h"

using std::string;

namespace hw3 {

// A FileIndexReader is used to access an index file, read the header
// information out of it,  and manufacture DocTableReader and
// IndexTableReader hash table accessors.  (To manufacture a
// DocIDTableReader, you use a manufactured IndexTableReader.)
class FileIndexReader {
  // This friend declaration is here so that the Test_FileIndexReader
  // unit test fixture can access protected member variables of
  // FileIndexReader.  See test_fileindexreader.h for details.
  friend class Test_FileIndexReader;

 public:
  // Arguments:
  //
  // - filename: the index file to load.
  //
  // - validate: whether to validate the checksums (default=true).
  FileIndexReader(string filename, bool validate = true);
  ~FileIndexReader();

  // Manufactures and returns a DocTableReader for this index file.
  // A DocTableReader is a HashTableReader subclass that is
  // specialized to read the docid-->filename hashtable within this
  // index file. (See DocTableReader.h for details.)
  DocTableReader GetDocTableReader();

  // Manufactures and returns an IndexTableReader for this index file.
  // An IndexTableReader is a HashTableReader subclass that is
  // specialized to read the word-->docidtable hashtable within this
  // index file. (See IndexTableReader.h for details.)
  IndexTableReader GetIndexTableReader();

  // Returns a const reference to the file header information.
  const IndexFileHeader &getHeader() const { return header_; }

 protected:
  // The name of the index file we're reading.
  string filename_;

  // The stdio.h (FILE *) for the file.
  FILE *file_;

  // A cached copy of file header.
  IndexFileHeader header_;

  // A cached copy of the index size field from the index header.
 IndexFileOffset_t index_size_;

 private:
  // Disable the copy constructor and assignment operator.  See
  // the following helpful Google C++ style guide entry for details
  // on how this works and why it is a good idea to do, when you can:
  //
  //    http://google-styleguide.googlecode.com/svn/trunk/
  //    cppguide.xml#Copy_Constructors
  DISALLOW_COPY_AND_ASSIGN(FileIndexReader);
};

}  // namespace hw3

#endif  // _HW3_FILEINDEXREADER_H_
