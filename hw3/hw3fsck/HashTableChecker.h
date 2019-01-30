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

#ifndef _HW3_HASHTABLECHECKER_H_
#define _HW3_HASHTABLECHECKER_H_

#include <stdint.h>  // for uint32_t, etc.
#include <cstdio>    // for (FILE *).
#include <list>      // for std::list.

namespace hw3 {

// A HashTableChecker is the base class for the different kinds
// of hash table readers.  Its subclasses are the DocTableChecker, the
// IndexTableChecker, and the DocPositionsReader.
class HashTableChecker {
  // This friend declaration is here so that the Test_HashTableChecker
  // unit test fixture can access protected member variables of
  // HashTableChecker.  See test_hashtablereader.h for details.
  friend class Test_HashTableChecker;

 public:
  // Construct a HashTableChecker reader.  Arguments:
  //
  // - f: an open (FILE *) for the underlying index file.  The
  //   constructed object takes ownership of the (FILE *) and will
  //   fclose() it on destruction.
  //
  // - offset: the hash table's byte offset within the file.
  HashTableChecker(FILE *f, uint32_t offset, uint32_t len);
  ~HashTableChecker();

  // We have to implement a copy constructor and assignment operator
  // to manage the (FILE *) that instances of HashTableChecker use.
  // If somebody uses a copy constructor to manufactur a new
  // HashTableChecker or the assignment operator to assign to an
  // existing one from another HashTableChecker, we want to duplicate
  // the (FILE *) so that the right fclose()-on-destruction behavior
  // takes place.
  HashTableChecker(const HashTableChecker &rhs);
  HashTableChecker &operator=(const HashTableChecker &rhs);

  // This function checks the hashtable for consistency.
  virtual void Check(uint32_t offset, uint32_t len);

  // This function is invoked by the checker when it is time for
  // it to evaluate an element within the hashtable.  Derived classes
  // need to override this function to provide table-type-specific
  // element checking. bucket_number is provided to verify that the
  // element's hash value lines up with the bucket correctly.
  virtual void CheckElement(uint32_t element_offset,
                            uint32_t bucket_number) = 0;

 protected:
  // The open (FILE *) stream associated with this hash table.
  FILE *file_;

  // The byte offset within the file that this hash table starts at.
  uint32_t offset_;

  // The length of the table, in bytes.
  uint32_t len_;

  // A cached copy of the total number of buckets in this hash table.
  uint32_t num_buckets_;
};

}  // namespace hw3

#endif  // _HW3_HASHTABLECHECKER_H_
