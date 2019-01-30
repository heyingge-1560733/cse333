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

#ifndef _HW1_LINKEDLIST_PRIV_H_
#define _HW1_LINKEDLIST_PRIV_H_

#include "./CSE333.h"      // for HWSize_t
#include "./LinkedList.h"  // for LinkedList and LLIter

// This file defines the internal structures associated with our LinkedList
// implementation.  Customers should not include this file or assume anything
// based on its contents.  Instead, we have broken these out into this file so
// that the unit test code for LinkedList has access to it, allowing unit
// tests to peek inside the implementation to check pointers and fields for
// correctness.

// This struct represents an individual node within a linked list.  A node
// contains next and prev pointers as well as a customer-supplied payload
// pointer.
typedef struct ll_node {
  LLPayload_t     payload;  // customer-supplied payload pointer
  struct ll_node *next;     // next node in list, or NULL
  struct ll_node *prev;     // prev node in list, or NULL
} LinkedListNode, *LinkedListNodePtr;

// This struct represents the entire linked list.  We provided a struct
// declaration (but not definition) in LinkedList.h; this is the associated
// definition.  This struct contains metadata about the linked list.
typedef struct ll_head {
  HWSize_t          num_elements;  //  # elements in the list
  LinkedListNodePtr head;  // head of linked list, or NULL if empty
  LinkedListNodePtr tail;  // tail of linked list, or NULL if empty
} LinkedListHead;

// This struct represents the state of an iterator.  We expose the struct
// declaration in LinkedList.h, but not the definition, similar to what we did
// above for the linked list itself.
typedef struct ll_iter {
  LinkedList        list;  // the list we're for
  LinkedListNodePtr node;  // the node we are at, or NULL if broken
} LLIterSt;

#endif  // _HW1_LINKEDLIST_PRIV_H_
