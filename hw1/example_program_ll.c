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
#include "LinkedList.h"

// the payload type we'll add
typedef struct {
  int num;
} ExamplePayload, *ExamplePayloadPtr;

// prototype of our payload free function
void ExamplePayloadFree(LLPayload_t payload);

// prototype of our payload comparator function
int ExamplePayloadComparator(LLPayload_t p1, LLPayload_t p2);

// our main function; here, we demonstrate how to use some
// of the linked list functions.
int main(int argc, char **argv) {
  ExamplePayloadPtr payload;
  LinkedList list;
  LLIter iter;
  int i;

  // allocate a list
  list = AllocateLinkedList();
  Verify333(list != NULL);

  // insert 100 elements
  for (i = 0; i < 100; i++) {
    payload = (ExamplePayloadPtr) malloc(sizeof(ExamplePayload));
    Verify333(payload != NULL);
    payload->num = i;
    Verify333(PushLinkedList(list, (LLPayload_t)payload) == 1);

    // make sure our list total is correct
    Verify333(NumElementsInLinkedList(list) == i+1);
  }

  // sort the list in descending order
  SortLinkedList(list, 0, &ExamplePayloadComparator);

  // pop off the first element
  Verify333(PopLinkedList(list, (LLPayload_t*) &payload) == 1);
  Verify333(payload->num == 99);
  Verify333(NumElementsInLinkedList(list) == 99);
  free(payload);

  // slice off the last element
  Verify333(SliceLinkedList(list, (LLPayload_t*) &payload) == 1);
  Verify333(payload->num == 0);
  Verify333(NumElementsInLinkedList(list) == 98);
  free(payload);

  // make an iterator from the head
  iter = LLMakeIterator(list, 0);
  Verify333(iter != NULL);

  // peek at the current iterator payload
  LLIteratorGetPayload(iter, (LLPayload_t*) &payload);
  Verify333(payload->num == 98);

  // move the iterator, peek at next payload
  Verify333(LLIteratorNext(iter) == 1);
  LLIteratorGetPayload(iter, (LLPayload_t*) &payload);
  Verify333(payload->num == 97);

  // free the iterator
  LLIteratorFree(iter);

  // free the linked list
  FreeLinkedList(list, &ExamplePayloadFree);
  return 0;
}


void ExamplePayloadFree(LLPayload_t payload) {
  Verify333(payload != NULL);
  free(payload);
}

// prototype of our payload comparator function
int ExamplePayloadComparator(LLPayload_t p1, LLPayload_t p2) {
  int i1, i2;
  Verify333(p1 != NULL);
  Verify333(p2 != NULL);

  i1 = ((ExamplePayloadPtr) p1)->num;
  i2 = ((ExamplePayloadPtr) p2)->num;

  if (i1 > i2)
    return 1;
  if (i1 < i2)
    return -1;
  return 0;
}
