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

#ifndef _HW2_FILEPARSER_H
#define _HW2_FILEPARSER_H

#include "libhw1/LinkedList.h"
#include "libhw1/HashTable.h"

// ReadFile reads the full contents of the file "filename" into memory,
// malloc'ing space for it and returning a pointer to the malloc'ed
// memory.  The caller is responsible for freeing the malloc'ed space.
//
// Arguments:
//
// - filename:  a string containing the pathname of the file to read
//
// - size: an output parameter through which we return the size of the
//         file, assuming we successfully read it in.
//
// Returns:
//
// - NULL if the read fails for any reason
//
// - Otherwise, a pointer to the memory buffer containing the file
//   content.  Note that ReadFile will add a NULL-terminator to the
//   end of the file content, so it is safe to treat the return value
//   as a string. On success, ReadFile returns the number of bytes
//   read from the file (not including the NULL-terminator we add)
//   through the "size" output parameter.
char *ReadFile(const char *filename, HWSize_t *size);

// As we scan through the contents of a file, we identify words within it, and
// for each unique word we find, we build up this structure.  It contains the
// word ("word"), as well as a linked list of positions that we found the word
// ("positions").
//
// We play a nasty trick; instead of malloc'ing space for the payload of the
// linked list, we instead cast the (DocPositionOffset_t) position into a (LLPayload_t) and
// store that as the payload.  Note we're assuming that pointers are 64 bits
// long in order to do this. This means when you free the linked list, you
// don't need to free the payload -- the payload free function needs to exist,
// but it should do nothing.
typedef struct WordPositions {
  char       *word;
  LinkedList  positions;
} WordPositions;

// BuildWordHT reads the file "filename" into memory and parses it, looking
// for words consisting entirely of alphabetic characters. (No punctuation, no
// whitespace, etc.).  For each unique word it finds, it transforms the word
// into all lowercase, builds a WordPositions structure, and it inserts that
// WordPositions structure into the hash table.  The key it uses to insert it
// is the FNVHash64() of the word (not including the word's NULL terminator);
// see libhw1/HashTable.h for FNVHash64().
//
// The caller is responsible for calling FreeWordHT() to free the memory
// associated with the hashtable.
//
// Alternatively, a caller can use a HashTable function to remove
// a WordPositions entry from the hashtable.  If it does so,
// the caller takes ownership of the memory; the three regions it
// needs to eventually free are:
//    (1) it needs to call FreeLinkedList() on the positions field;
//        see the comment above the typedef of the WordPositions
//        field to understand how the LinkedList payload works
//        in a WordPositions.
//    (2) it needs to free() the word field;
//    (3) it needs to free() the WordPositions structure itself.
//
// Arguments:
//  - filename: the name of the file to build the hash table.
//
// Returns:
//
// - on failure (e.g., out of memory, or the file couldn't be read),
//   returns NULL.
//
// - on success, returns a HashTable, where each HTKeyValue contains
//     key:   FNVHash64(word)
//     value: a malloc'ed WordPositions structure for that word
HashTable BuildWordHT(char *filename);

// Frees all of the memory malloc'ed to build a word hashtable
// returned by BuildWordHT().
void FreeWordHT(HashTable table);

#endif  // _HW2_FILEPARSER_H
