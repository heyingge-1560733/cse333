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

#ifndef _HW1_HASHTABLE_PRIV_H_
#define _HW1_HASHTABLE_PRIV_H_

#include "./CSE333.h"
#include "./LinkedList.h"
#include "./HashTable.h"

// Define the internal, private structs and helper functions associated with a
// HashTable.

// This is the struct that we use to represent a hash table. Quite simply, a
// hash table is just an array of buckets, where each bucket is a linked list
// of HTKeyValue structs.
typedef struct htrec {
  HWSize_t        num_buckets;   // # of buckets in this HT?
  HWSize_t        num_elements;  // # of elements currently in this HT?
  LinkedList     *buckets;       // the array of buckets
} HashTableRecord;

// This is the struct we use to represent an iterator.
typedef struct ht_itrec {
  bool       is_valid;    // is this iterator valid?
  HashTable  ht;          // the HT we're pointing into
  HWSize_t   bucket_num;  // which bucket are we in?
  LLIter     bucket_it;   // iterator for the bucket, or NULL
} HTIterRecord;

// This is the internal hash function we use to map from HTKey_t keys to a
// HWSize_t bucket number.
HWSize_t HashKeyToBucketNum(HashTable ht, HTKey_t key);

#endif  // _HW1_HASHTABLE_PRIV_H_
