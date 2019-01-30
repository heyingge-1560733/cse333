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

Inside this directory, you'll find the following:

 - Makefile: the gnu Makefile to compile hw1; to run it, just type
   "make" at the command line

 - Makefile.coverage: recompiles test_suite with gcov's code
   coverage instrumentation, and generates the coverage data.
   Once you have your code working, type "make -f Makefile.coverage"
   to produce the data, then look at LinkedList.c.gcov and
   HashTable.c.gcov to see the actual coverage data.

 - LinkedList.h: the public header for the doubly-linked list module.
   This header contains all of the definitions, typedefs, and function
   prototypes upon which customers depend.

 - LinkedList_priv.h: a private header to expose some of the internal
   implementation details of the linked list module.  The unit test
   code uses this private header to get access to those internals.

 - LinkedList.c: the implementation of the linked list module.

 - HashTable.h, HashTable_priv.h, HashTable.c: similar to the linked list
   files, but for a chained hash table implementation.

 - test_*.cc, test_*.h: the unit test code.  Look at test_linkedlist.cc
   for an example of the unit tests that exercise the linked list.

After you compile, you'll have access to two executables:

 - test_suite:  run the unit tests against your code.  This will
   crash out and print an error if a unit test fails.  Once you're
   able to make it all the way through, your code is doing pretty
   well. Try to come up with other test cases we might not have
   implemented, of course.

 - example_program_ll, example_program_ht:  exercises the linked list
   and hash table code, respectively.


