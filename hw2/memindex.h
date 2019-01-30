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

#ifndef _HW2_MEMINDEX_H
#define _HW2_MEMINDEX_H

#include <stdint.h>
#include "./doctable.h"
#include "libhw1/LinkedList.h"
#include "libhw1/HashTable.h"

// An offset of a token within a document.
typedef uint32_t DocPositionOffset_t;

// A MemIndex represents an in-memory inverted index, containing a set of
// mappings.  Each mapping maps from a word to a list of documents that
// contain the word, including a list of positions within the document that
// the word appears.  A MemIndex is simply a HashTable.
typedef HashTable MemIndex;

// The following structure represents a document that
// matched a search query.  When a customer issues a query
// against a MemIndex, the MemIndex will construct and
// return a LinkedList of SearchResults, sorted in decreasing
// quality (i.e., the rank field).
typedef struct SearchResult {
  DocID_t docid;  // a document that matches a search query
  HWSize_t rank;   // an indicator of the quality of the match
} SearchResult, *SearchResultPtr;

// Allocate a new MemIndex.  Returns NULL on failure, non-NULL
// on success.
MemIndex AllocateMemIndex(void);

// Frees a previously allocated MemIndex, including all space
// malloc'ed within it.
void FreeMemIndex(MemIndex index);

// Returns the number of words contained within the index.
HWSize_t MINumWordsInMemIndex(MemIndex index);

// Adds a "posting list" to the MemIndex.  A "posting list" contains
// the set of positions within a document that a particular word
// appears.  So, the argument "word" indicates the word that this
// posting list is for and the "docid" argument indicates the docID
// this posting list is for; the word "word" appears in the document
// "docid" in the list of positions (in ascending order) specified by
// the "positions" list.  The "positions" list must be non-empty.
//
// memindex takes ownership of "word" and "positions."
//
// Returns 0 on failure, 1 on success.
int MIAddPostingList(MemIndex index, char *word, DocID_t docid,
                     LinkedList positions);

// Processes a query against the memindex, and returns a list
// of SearchResults.  The customer is responsible for freeing
// the list of SearchResults; the appropriate free function pointer
// to pass in to FreeLinkedList is stdlib's free().
//
// Arguments:
//
// - index: the MemIndex to query
//
// - query: a non-zero-lengthed array of strings; each string is
//          query word, all lower-case.  MIProcessQuery will return a
//          list of SearchResults containing all documents that contain
//          every query word at least once.
//
// - qlen: the number of query words in the query array.
//
// Returns:
//
// - NULL if no matching documents were found
//
// - a non-NULL LinkedList containing a list of SearchResults
//   if at least one matching document was found.  The caller
//   is responsible freeing the linked list (see above).
LinkedList MIProcessQuery(MemIndex index, char *query[], uint8_t qlen);

// In HW3, customers will need to directly access the contents of
// the MemIndex HashTable.  The HashTable, like all HashTables, contains
// HTKeyValues;  the value field is a pointer to a WordDocSet
// structure, defined below.
//
// A MemIndex is a HashTable that maps from a word to a WordDocSet.
// Each WordDocSet contains another HashTable that maps from docID to
// a linked list of hits within that docID.  Compare this structure
// to the figure in the HW2 web page that depicts an inverted index,
// and you'll see where it fits in.
typedef struct {
  char       *word;
  HashTable   docIDs;
} WordDocSet, *WordDocSetPtr;

#endif  // _HW2_MEMINDEX_
