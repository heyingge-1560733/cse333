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

#ifndef _HW3_HASHTABLEREADER_H_
#define _HW3_HASHTABLEREADER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <cstdio>    // for (FILE *).
#include <list>      // for std::list.

#include "./filelayout.h"

namespace hw3 {

// A HashTableReader is the base class for the different kinds
// of hash table readers.  Its subclasses are the DocTableReader, the
// IndexTableReader, and the DocPositionsReader.
class HashTableReader {
  // This friend declaration is here so that the Test_HashTableReader
  // unit test fixture can access protected member variables of
  // HashTableReader.  See test_hashtablereader.h for details.
  friend class Test_HashTableReader;

  // Similarly, the debug printing method needs access to objects
  // of this class.
  friend void dumpFileIndex(const char*);

 public:
  // Construct a HashTableReader reader.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed object takes ownership of the (FILE *) and will
  //   fclose() it on destruction.
  //
  // - offset: the hash table's byte offset within the file.
  HashTableReader(FILE *f, IndexFileOffset_t offset);
  ~HashTableReader();

  // We have to implement a copy constructor and assignment operator
  // to manage the (FILE *) that instances of HashTableReader use.
  // If somebody uses a copy constructor to manufactur a new
  // HashTableReader or the assignment operator to assign to an
  // existing one from another HashTableReader, we want to duplicate
  // the (FILE *) so that the right fclose()-on-destruction behavior
  // takes place.
  HashTableReader(const HashTableReader &rhs);
  HashTableReader &operator=(const HashTableReader &rhs);

  // Given a 64-bit hash key, this function navigates through
  // the on-disk hash table and returns a list of file offsets of
  // "element" fields within the bucket that the hash key maps to.
  // Only subclasses may invoke this.
  //
  // Arguments:
  //
  // - hashval: the 64-bit hash key to look up.
  //
  // Returns:
  //
  // - A list of offsets of "element" fields inside the bucket that
  //   the hash value maps to.  If no elements are in the  bucket,
  //   this returns an empty list.
  std::list<IndexFileOffset_t> LookupElementPositions(HTKey_t hashval);

 protected:
  // The open (FILE *) stream associated with this hash table.
  FILE *file_;

  // The byte offset within the file that this hash table starts at.
  IndexFileOffset_t offset_;

  // A cached copy of the total number of buckets in this hash table.
  BucketListHeader header_;
  //uint32_t num_buckets_;
};

}  // namespace hw3

#endif  // _HW3_HASHTABLEREADER_H_
