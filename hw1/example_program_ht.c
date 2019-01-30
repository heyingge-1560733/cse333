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

#include <stdio.h>
#include <stdlib.h>

#include "CSE333.h"
#include "HashTable.h"

typedef struct {
  int num;
} ExampleValue, *ExampleValuePtr;

// prototype of our free function
void ExampleValueFree(HTValue_t value);

// our main function; here, we demonstrate how to use some
// of the hash table functions
int main(int argc, char **argv) {
  ExampleValuePtr evp;
  HashTable ht;
  HTIter iter;
  HTKeyValue kv, old_kv;
  HTKey_t i;

  // allocate a hash table with 10,000 initial buckets
  ht = AllocateHashTable(10000);
  Verify333(ht != NULL);

  // insert 20,000 elements (load factor = 2.0)
  for (i = 0; i < 20000; i++) {
    evp = (ExampleValuePtr) malloc(sizeof(ExampleValue));
    Verify333(evp != NULL);
    evp->num = i;

    // make sure HT has the right # of elements in it to start
    Verify333(NumElementsInHashTable(ht) == (HWSize_t) i);

    // insert a new element
    kv.key = FNVHashInt64((HTValue_t)i);
    kv.value = (HTValue_t)evp;
    Verify333(InsertHashTable(ht, kv, &old_kv) == 1);

    // make sure hash table has right # of elements post-insert
    Verify333(NumElementsInHashTable(ht) == (HWSize_t) (i+1));
  }

  // look up a few values
  Verify333(LookupHashTable(ht, FNVHashInt64((HTValue_t)100), &kv) == 1);
  Verify333(kv.key == FNVHashInt64((HTValue_t)100));
  Verify333(((ExampleValuePtr) kv.value)->num == 100);

  Verify333(LookupHashTable(ht, FNVHashInt64((HTValue_t)18583), &kv) == 1);
  Verify333(kv.key == FNVHashInt64((HTValue_t)18583));
  Verify333(((ExampleValuePtr) kv.value)->num == 18583);

  // make sure non-existent value cannot be found
  Verify333(LookupHashTable(ht, FNVHashInt64((HTValue_t)20000), &kv) == 0);

  // delete a value
  Verify333(RemoveFromHashTable(ht, FNVHashInt64((HTValue_t)100), &kv) == 1);
  Verify333(kv.key == FNVHashInt64((HTValue_t)100));
  Verify333(((ExampleValuePtr) kv.value)->num == 100);
  ExampleValueFree(kv.value);   // since we malloc'ed it, we must free it

  // make sure it's deleted
  Verify333(LookupHashTable(ht, FNVHashInt64((HTValue_t)100), &kv) == 0);
  Verify333(NumElementsInHashTable(ht) == (HWSize_t) 19999);

  // loop through using an iterator
  i = 0;
  iter = HashTableMakeIterator(ht);
  Verify333(iter != NULL);

  while (HTIteratorPastEnd(iter) == 0) {
    Verify333(HTIteratorGet(iter, &kv) == 1);
    Verify333(kv.key != FNVHashInt64((HTValue_t)100));   // we deleted it

    // advance the iterator
    HTIteratorNext(iter);
    i++;
  }
  Verify333(i == 19999);

  // free the iterator
  HTIteratorFree(iter);

  // free the hash table
  FreeHashTable(ht, &ExampleValueFree);
  return 0;
}

void ExampleValueFree(HTValue_t value) {
  Verify333(value != NULL);
  free(value);
}
