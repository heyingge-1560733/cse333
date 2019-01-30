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
#include <stdint.h>
#include <string.h>

extern "C" {
  #include "./doctable.h"
}

#include "./test_suite.h"
#include "./test_doctable.h"

namespace hw2 {

TEST_F(Test_DocTable, DTTestSimple) {
  DocTable t1;
  const char *f1 = "foo/bar/baz.txt", *f2 = "bar/baz.txt";
  char *fres;
  DocID_t d1, d2, dres;

  t1 = AllocateDocTable();
  ASSERT_NE(static_cast<DocTable>(NULL), t1);
  ASSERT_EQ(0U, DTNumDocsInDocTable(t1));
  HW2Addpoints(5);

  d1 = DTRegisterDocumentName(t1, const_cast<char *>(f1));
  ASSERT_NE(0U, d1);
  ASSERT_EQ(1U, DTNumDocsInDocTable(t1));
  d2 = DTRegisterDocumentName(t1, const_cast<char *>(f2));
  ASSERT_NE(0U, d2);
  ASSERT_EQ(2U, DTNumDocsInDocTable(t1));
  HW2Addpoints(5);

  dres = DTRegisterDocumentName(t1, const_cast<char *>(f2));
  ASSERT_EQ(d2, dres);
  dres = DTRegisterDocumentName(t1, const_cast<char *>(f1));
  ASSERT_EQ(d1, dres);
  HW2Addpoints(5);

  dres = DTLookupDocumentName(t1, const_cast<char *>(f1));
  ASSERT_EQ(d1, dres);
  dres = DTLookupDocumentName(t1, const_cast<char *>("nonexistent/file"));
  ASSERT_EQ(0U, dres);
  fres = DTLookupDocID(t1, d1);
  ASSERT_EQ(0, strcmp(fres, f1));
  fres = DTLookupDocID(t1, static_cast<uint64_t>(0xDEADBEEF));
  ASSERT_EQ(static_cast<char *>(NULL), fres);
  HW2Addpoints(5);

  FreeDocTable(t1);
  HW2Addpoints(10);
}

}  // namespace hw2
