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

extern "C" {
  #include "./memindex.h"
  #include "./filecrawler.h"
}

#include "./test_suite.h"
#include "./test_memindex.h"

namespace hw2 {

TEST_F(Test_MemIndex, MITestSimple) {
  int res;
  DocTable dt;
  MemIndex idx;
  LinkedList llres;
  LLIter lit;
  unsigned int i;

  const char *q1[] = {"equations"};
  const char *q2[] = {"report", "normal"};
  const char *q3[] = {"report", "suggestions", "normal"};
  const char *q4[] = {"report", "normal", "foobarbaz"};


  // Crawl part of the file tree.
  res = CrawlFileTree(const_cast<char *>("./test_tree/bash-4.2/support"),
                      &dt, &idx);
  ASSERT_EQ(res, 1);
  ASSERT_EQ(MINumWordsInMemIndex(idx), 3852U);

  // Process query 1, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q1), 1);
  ASSERT_NE((LinkedList) NULL, llres);
  ASSERT_EQ(NumElementsInLinkedList(llres), 2U);
  lit = LLMakeIterator(llres, 0);
  for (i = 0; i < NumElementsInLinkedList(llres); i++) {
    SearchResult *res;

    LLIteratorGetPayload(lit, reinterpret_cast<LLPayload_t*>(&res));
    if (i == 0) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/texi2html"), 0);
    } else if (i == 1) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/man2html.c"), 0);
    }
    LLIteratorNext(lit);
  }
  LLIteratorFree(lit);
  FreeLinkedList(llres, reinterpret_cast<LLPayloadFreeFnPtr>(&free));
  HW2Addpoints(20);

  // Process query 2, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q2), 2);
  ASSERT_NE((LinkedList) NULL, llres);
  ASSERT_EQ(NumElementsInLinkedList(llres), 2U);
  lit = LLMakeIterator(llres, 0);
  for (i = 0; i < NumElementsInLinkedList(llres); i++) {
    SearchResult *res;

    LLIteratorGetPayload(lit, reinterpret_cast<LLPayload_t*>(&res));
    if (i == 0) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/texi2html"), 0);
    } else if (i == 1) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/man2html.c"), 0);
    }
    LLIteratorNext(lit);
  }
  LLIteratorFree(lit);
  FreeLinkedList(llres, reinterpret_cast<LLPayloadFreeFnPtr>(&free));
  HW2Addpoints(20);

  // Process query 3, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q3), 3);
  ASSERT_NE((LinkedList) NULL, llres);
  ASSERT_EQ(NumElementsInLinkedList(llres), 1U);
  lit = LLMakeIterator(llres, 0);
  for (i = 0; i < NumElementsInLinkedList(llres); i++) {
    SearchResult *res;

    LLIteratorGetPayload(lit, reinterpret_cast<LLPayload_t*>(&res));
    if (i == 0) {
      char *docname = DTLookupDocID(dt, res->docid);
      ASSERT_EQ(
         strcmp(docname,
                "./test_tree/bash-4.2/support/texi2html"), 0);
    }
    LLIteratorNext(lit);
  }
  LLIteratorFree(lit);
  FreeLinkedList(llres, reinterpret_cast<LLPayloadFreeFnPtr>(&free));
  HW2Addpoints(20);

  // Process query 4, check results.
  llres = MIProcessQuery(idx, const_cast<char **>(q4), 3);
  ASSERT_EQ((LinkedList) NULL, llres);
  HW2Addpoints(20);

  // Free up everything.
  FreeDocTable(dt);
  FreeMemIndex(idx);
  HW2Addpoints(10);
}

}  // namespace hw2
