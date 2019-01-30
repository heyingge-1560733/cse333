// Yingge He
// 1560733
// heyingge@uw.edu
/*
 * Copyright ©2018 Justin Hsia, Yingge He.  All rights reserved.  Permission is
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
#include <stdint.h>

#include "CSE333.h"
#include "HashTable.h"
#include "HashTable_priv.h"

// A private utility function to grow the hashtable (increase
// the number of buckets) if its load factor has become too high.
static void ResizeHashtable(HashTable ht);

// This is a helper funciton to find if a linkedlist contains the specific key.
// Return true if found; return false if not.
static bool KeyIsFound(LinkedList list, LLIter iter, HTKey_t key);

// a free function that does nothing
static void LLNullFree(LLPayload_t freeme) { }
static void HTNullFree(HTValue_t freeme) { }

HashTable AllocateHashTable(HWSize_t num_buckets) {
  HashTable ht;
  HWSize_t  i;

  // defensive programming
  if (num_buckets == 0) {
    return NULL;
  }

  // allocate the hash table record
  ht = (HashTable) malloc(sizeof(HashTableRecord));
  if (ht == NULL) {
    return NULL;
  }

  // initialize the record
  ht->num_buckets = num_buckets;
  ht->num_elements = 0;
  ht->buckets =
    (LinkedList *) malloc(num_buckets * sizeof(LinkedList));
  if (ht->buckets == NULL) {
    // make sure we don't leak!
    free(ht);
    return NULL;
  }
  for (i = 0; i < num_buckets; i++) {
    ht->buckets[i] = AllocateLinkedList();
    if (ht->buckets[i] == NULL) {
      // allocating one of our bucket chain lists failed,
      // so we need to free everything we allocated so far
      // before returning NULL to indicate failure.  Since
      // we know the chains are empty, we'll pass in a
      // free function pointer that does nothing; it should
      // never be called.
      HWSize_t j;
      for (j = 0; j < i; j++) {
        FreeLinkedList(ht->buckets[j], LLNullFree);
      }
      free(ht->buckets);
      free(ht);
      return NULL;
    }
  }

  return (HashTable) ht;
}

void FreeHashTable(HashTable table,
                   ValueFreeFnPtr value_free_function) {
  HWSize_t i;

  Verify333(table != NULL);  // be defensive

  // loop through and free the chains on each bucket
  for (i = 0; i < table->num_buckets; i++) {
    LinkedList  bl = table->buckets[i];
    HTKeyValue *nextKV;

    // pop elements off the the chain list, then free the list
    while (NumElementsInLinkedList(bl) > 0) {
      Verify333(PopLinkedList(bl, (LLPayload_t*)&nextKV));
      value_free_function(nextKV->value);
      free(nextKV);
    }
    // the chain list is empty, so we can pass in the
    // null free function to FreeLinkedList.
    FreeLinkedList(bl, LLNullFree);
  }

  // free the bucket array within the table record,
  // then free the table record itself.
  free(table->buckets);
  free(table);
}

HWSize_t NumElementsInHashTable(HashTable table) {
  Verify333(table != NULL);
  return table->num_elements;
}

HTKey_t FNVHash64(unsigned char *buffer, HWSize_t len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //
  // http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;

  /*
   * FNV-1a hash each octet of the buffer
   */
  while (bp < be) {
    /* xor the bottom with the current octet */
    hval ^= (uint64_t) * bp++;
    /* multiply by the 64 bit FNV magic prime mod 2^64 */
    hval *= FNV_64_PRIME;
  }
  /* return our new hash value */
  return hval;
}

HTKey_t FNVHashInt64(HTValue_t hashval) {
  unsigned char buf[8];
  int i;
  uint64_t hashme = (uint64_t)hashval;

  for (i = 0; i < 8; i++) {
    buf[i] = (unsigned char) (hashme & 0x00000000000000FFULL);
    hashme >>= 8;
  }
  return FNVHash64(buf, 8);
}

HWSize_t HashKeyToBucketNum(HashTable ht, HTKey_t key) {
  return key % ht->num_buckets;
}

int InsertHashTable(HashTable table,
                    HTKeyValue newkeyvalue,
                    HTKeyValue *oldkeyvalue) {
  HWSize_t insertbucket;
  LinkedList insertchain;

  Verify333(table != NULL);
  ResizeHashtable(table);

  // calculate which bucket we're inserting into,
  // grab its linked list chain
  insertbucket = HashKeyToBucketNum(table, newkeyvalue.key);
  insertchain = table->buckets[insertbucket];

  // initialize a HTKeyValue Struct with newkey and new value
  HTKeyValuePtr copy = (HTKeyValuePtr)malloc(sizeof(HTKeyValue));
  if (copy == NULL)
    return 0;  // out of memory
  copy->key = newkeyvalue.key;
  copy->value = newkeyvalue.value;

  // if it's an empty list, just add to it
  if (NumElementsInLinkedList(insertchain) == 0U) {
    if (!PushLinkedList(insertchain, (LLPayload_t)copy)) {
      free(copy);
      return 0;  // fail to push
    }

    // push succeed
    table->num_elements++;  // update size
    return 1;  // push succeed
  }

  LLIter iter = LLMakeIterator(insertchain, 0);
  if (iter == NULL) {
    free(copy);
    return 0;  // out of memory
  }

  // the key in newkeyvalue is already present in the HashTable
  if (KeyIsFound(insertchain, iter, newkeyvalue.key)) {
    // assign oldkey and oldvalue to the return parameter
    HTKeyValuePtr oldpayload;
    LLIteratorGetPayload(iter, (LLPayload_t*)(&oldpayload));
    oldkeyvalue->key = oldpayload->key;
    oldkeyvalue->value = oldpayload->value;

    // assign new value to existing bucket
    oldpayload->value = newkeyvalue.value;
    free(copy);
    LLIteratorFree(iter);
    return 2;
  }

  LLIteratorFree(iter);
  // key not found, just push
  if (!PushLinkedList(insertchain, (LLPayload_t)copy)) {
    free(copy);
    return 0;  // fail to push
  }

  table->num_elements++;  // update size
  return 1;  // push succeed
}

int LookupHashTable(HashTable table,
                    HTKey_t key,
                    HTKeyValue *keyvalue) {
  Verify333(table != NULL);

  // calculate which bucket we're inserting into,
  // grab its linked list chain
  HWSize_t insertbucket = HashKeyToBucketNum(table, key);
  LinkedList insertchain = table->buckets[insertbucket];

  // if the list is empty, return 0
  if (NumElementsInLinkedList(insertchain) == 0U)
    return 0;

  LLIter iter = LLMakeIterator(insertchain, 0);
  if (iter == NULL) {
    return -1;  // out of memory
  }

  if (KeyIsFound(insertchain, iter, key)) {
    LLPayload_t payload;
    LLIteratorGetPayload(iter, &payload);
    HTValue_t curr_value = ((HTKeyValuePtr)payload)->value;
    keyvalue->key = key;
    keyvalue->value = curr_value;

    LLIteratorFree(iter);
    return 1;  // success
  }
  LLIteratorFree(iter);
  return 0;  // the key wasn't found in the HashTable
}

int RemoveFromHashTable(HashTable table,
                        HTKey_t key,
                        HTKeyValue *keyvalue) {
  Verify333(table != NULL);

  // calculate which bucket we're inserting into,
  // grab its linked list chain
  HWSize_t insertbucket = HashKeyToBucketNum(table, key);
  LinkedList insertchain = table->buckets[insertbucket];

  // if the list is empty, return 0
  if (NumElementsInLinkedList(insertchain) == 0U)
    return 0;

  LLIter iter = LLMakeIterator(insertchain, 0);
  if (iter == NULL)
    return -1;  // out of memory

  // if key is not found, return 0
  if (!KeyIsFound(insertchain, iter, key)) {
    LLIteratorFree(iter);
    return 0;
  }

  // fetch the current key and value
  LLPayload_t payload;
  LLIteratorGetPayload(iter, &payload);
  HTValue_t value = ((HTKeyValuePtr)payload)->value;

  // set up the return parameter
  keyvalue->key = key;
  keyvalue->value = value;

  // free the payload that we allocate when inserted it
  free(payload);

  LLIteratorDelete(iter, &LLNullFree);

  table->num_elements--;  // update number of elements in HashTable
  LLIteratorFree(iter);
  return 1;  // success
}

HTIter HashTableMakeIterator(HashTable table) {
  HTIterRecord *iter;
  HWSize_t      i;

  Verify333(table != NULL);  // be defensive

  // malloc the iterator
  iter = (HTIterRecord *) malloc(sizeof(HTIterRecord));
  if (iter == NULL) {
    return NULL;
  }

  // if the hash table is empty, the iterator is immediately invalid,
  // since it can't point to anything.
  if (table->num_elements == 0) {
    iter->is_valid = false;
    iter->ht = table;
    iter->bucket_it = NULL;
    return iter;
  }

  // initialize the iterator.  there is at least one element in the
  // table, so find the first element and point the iterator at it.
  iter->is_valid = true;
  iter->ht = table;
  for (i = 0; i < table->num_buckets; i++) {
    if (NumElementsInLinkedList(table->buckets[i]) > 0) {
      iter->bucket_num = i;
      break;
    }
  }
  Verify333(i < table->num_buckets);  // make sure we found it.
  iter->bucket_it = LLMakeIterator(table->buckets[iter->bucket_num], 0UL);
  if (iter->bucket_it == NULL) {
    // out of memory!
    HTIteratorFree(iter);
    iter = NULL;
    return NULL;
  }
  return iter;
}

void HTIteratorFree(HTIter iter) {
  Verify333(iter != NULL);

  if (iter->bucket_it != NULL) {
    LLIteratorFree(iter->bucket_it);
  }
  free(iter);
}

int HTIteratorNext(HTIter iter) {
  Verify333(iter != NULL);

  // if pass the end of the table, return 0
  if (HTIteratorPastEnd(iter) == 1) {
    iter->is_valid = false;
    return 0;
  }

  // LinkedList iterator can't move forward
  if (LLIteratorNext(iter->bucket_it))
    return 1;  // LinkedList has the next node
  HWSize_t bucket_num = iter->bucket_num;
  HWSize_t num_buckets = iter->ht->num_buckets;
  HashTableRecord *table = iter->ht;

  // find the next non-empty list
  for (HWSize_t i = bucket_num + 1U; i < num_buckets; i++) {
    if (NumElementsInLinkedList(table->buckets[i]) > 0) {
      LLIteratorFree(iter->bucket_it);
      iter->bucket_num = i;
      iter->bucket_it = LLMakeIterator(iter->ht->buckets[i], 0);
      return 1;  // success
    }
  }
  iter->is_valid = false;
  return 0;  // at the end of table
}

int HTIteratorPastEnd(HTIter iter) {
  Verify333(iter != NULL);

  if (!iter->is_valid ||
      iter->ht->num_elements == 0) {
    iter->is_valid = false;
    return 1;  // iter is past the end of the table or the table is empty
  } else {
    return 0;  // iter is not at the end of the table
  }
}

int HTIteratorGet(HTIter iter, HTKeyValue *keyvalue) {
  Verify333(iter != NULL);

  // if the iterator is not valid or the table is empty, return 0
  if (!iter->is_valid || iter->ht->num_elements == 0) {
    return 0;
  } else {
    LLPayload_t payload;
    LLIteratorGetPayload(iter->bucket_it, &payload);
    *keyvalue = *(HTKeyValuePtr)payload;
    return 1;  // success
  }
}

int HTIteratorDelete(HTIter iter, HTKeyValue *keyvalue) {
  HTKeyValue kv;
  int res, retval;

  Verify333(iter != NULL);

  // Try to get what the iterator is pointing to.
  res = HTIteratorGet(iter, &kv);
  if (res == 0)
    return 0;

  // Advance the iterator.
  res = HTIteratorNext(iter);
  if (res == 0) {
    retval = 2;
  } else {
    retval = 1;
  }
  res = RemoveFromHashTable(iter->ht, kv.key, keyvalue);
  Verify333(res == 1);
  Verify333(kv.key == keyvalue->key);
  Verify333(kv.value == keyvalue->value);

  return retval;
}

static void ResizeHashtable(HashTable ht) {
  // Resize if the load factor is > 3.
  if (ht->num_elements < 3 * ht->num_buckets)
    return;

  // This is the resize case.  Allocate a new hashtable,
  // iterate over the old hashtable, do the surgery on
  // the old hashtable record and free up the new hashtable
  // record.
  HashTable newht = AllocateHashTable(ht->num_buckets * 9);

  // Give up if out of memory.
  if (newht == NULL)
    return;

  // Loop through the old ht with an iterator,
  // inserting into the new HT.
  HTIter it = HashTableMakeIterator(ht);
  if (it == NULL) {
    // Give up if out of memory.
    FreeHashTable(newht, &HTNullFree);
    return;
  }

  while (HTIteratorPastEnd(it) == 0) {
    HTKeyValue item, dummy;

    Verify333(HTIteratorGet(it, &item) == 1);
    if (InsertHashTable(newht, item, &dummy) != 1) {
      // failure, free up everything, return.
      HTIteratorFree(it);
      FreeHashTable(newht, &HTNullFree);
      return;
    }
    HTIteratorNext(it);
  }

  // Worked!  Free the iterator.
  HTIteratorFree(it);

  // Sneaky: swap the structures, then free the new table,
  // and we're done.
  {
    HashTableRecord tmp;

    tmp = *ht;
    *ht = *newht;
    *newht = tmp;
    FreeHashTable(newht, &HTNullFree);
  }

  return;
}

static bool KeyIsFound(LinkedList list, LLIter iter, HTKey_t key) {
  while (1) {
    if (NumElementsInLinkedList(list) == 0U) {
      return false;  // return false if empty list
    }

    // fetch the key of node that the iterator is pointing at
    LLPayload_t payload;
    LLIteratorGetPayload(iter, &payload);
    HTKey_t curr_key = ((HTKeyValuePtr)payload)->key;

    if (key == curr_key)
      return true;  // return true if key is found
    if (!LLIteratorHasNext(iter))
      return false;  // return false if at the last node
    LLIteratorNext(iter);  // forward iterator to the next node
  }
}
