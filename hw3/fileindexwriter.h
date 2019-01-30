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

#ifndef _HW3_FILEINDEXWRITER_H_
#define _HW3_FILEINDEXWRITER_H_

#include <stdint.h>  // [C++ doesn't yet standardize <cstdint>.]

// Include the HW1 LinkedList and HashTable headers, and the HW2
// MemIndex and DocTable headers.  We'll need these to access the
// routines in the libhw1.a and libhw2.a libraries.  Note that those
// libraries were compiled with gcc, and therefore have "C"-style
// linkage.  Since fileindexwriter.cc is compiled by g++, we need
// do use 'extern "C"' to tell g++ that the routines accessed through
// these header files were compiled with g++.
extern "C" {
  #include "libhw1/LinkedList.h"
  #include "libhw1/HashTable.h"
  #include "libhw2/memindex.h"
  #include "libhw2/doctable.h"
}

namespace hw3 {

// The WriteIndex() function writes the contents of a MemIndex and the
// docid_to_docname mapping of a DocTable into an index file.  The
// on-disk representation is defined in detail on the hw3 web page.
//
// Arguments:
//   - mi: the MemIndex to write into the index file.
//
//   - dt: the DocTable to write into the index file.
//
//   - filename: a C-style string containing the name of the index
//     file that we should create.
//
// Returns:
//   - the resulting size of the index file, in bytes, or 0 on error.
HWSize_t WriteIndex(MemIndex mi, DocTable dt, const char *filename);

}  // namespace hw3

#endif  // _HW3_FILEINDEXWRITER_H_
