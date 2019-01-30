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

#ifndef _HW3_FILEINDEXCHECKER_H_
#define _HW3_FILEINDEXCHECKER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <string>    // for std::string
#include <cstdio>    // for (FILE *)

#include "./fileindexutil.h"    // for DISALLOW_COPY_AND_ASSIGN()

using namespace std;

namespace hw3 {

// A FileIndexChecker is used to access an index file, validate the
// header information out of it, and manufacture DocTableChecker and
// IndexTableChecker hash table accessors.  (To manufacture a
// DocIDTableChecker, you use a manufactured IndexTableChecker.)
class FileIndexChecker {
 public:
  // Arguments:
  //
  // - filename: the index file to load.
  FileIndexChecker(string filename);
  ~FileIndexChecker();

 protected:
  // The name of the index file we're checking.
  string filename_;

  // The stdio.h (FILE *) for the file.
  FILE *file_;

  // A cached copy of the doctable size field from the index header.
  uint32_t doctable_size_;

  // A cached copy of the index size field from the index header.
  uint32_t index_size_;

 private:
  // Disable the copy constructor and assignment operator.  See
  // the following helpful Google C++ style guide entry for details
  // on how this works and why it is a good idea to do, when you can:
  //
  //    http://google-styleguide.googlecode.com/svn/trunk/
  //    cppguide.xml#Copy_Constructors
  DISALLOW_COPY_AND_ASSIGN(FileIndexChecker);
};

}  // namespace hw3

#endif  // _HW3_FILEINDEXCHECKER_H_
