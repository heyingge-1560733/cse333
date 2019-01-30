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
  #include "./fileparser.h"
}

#include "./test_suite.h"
#include "./test_fileparser.h"

namespace hw2 {

TEST_F(Test_FileParser, FPTestReadFile) {
  char *filebuf = NULL;
  HWSize_t len = 0;

  // read a big file
  filebuf = ReadFile(const_cast<char *>("./test_tree/books/paradiselost.txt"),
                     &len);
  ASSERT_NE(static_cast<char *>(NULL), filebuf);
  ASSERT_EQ(len, 495687U);
  ASSERT_EQ(filebuf[0], 'T');
  ASSERT_EQ(filebuf[495686], static_cast<char>(0x0a));
  free(filebuf);
  HW2Addpoints(10);

  // try to read a non-existent file
  filebuf = ReadFile(const_cast<char *>("bogus/file"), &len);
  ASSERT_EQ(static_cast<char *>(NULL), filebuf);
  HW2Addpoints(10);

  // read a small file
  filebuf = ReadFile(const_cast<char *>("./test_tree/bash-4.2/trap.h"), &len);
  ASSERT_NE(static_cast<char *>(NULL), filebuf);
  ASSERT_EQ(len, 3213U);
  ASSERT_EQ(filebuf[0], '/');
  ASSERT_EQ(filebuf[3212], static_cast<char>(0x0a));
  free(filebuf);
  HW2Addpoints(10);

  // try to read a file that contains non-ASCII text
  filebuf = ReadFile(const_cast<char *>("./test_tree./libhw1.a"), &len);
  ASSERT_EQ(static_cast<char *>(NULL), filebuf);
  HW2Addpoints(10);
}

TEST_F(Test_FileParser, FPTestBuildWordHT) {
  HashTable tab =
    BuildWordHT(const_cast<char *>("./test_tree/bash-4.2/doc/README"));
  ASSERT_NE(static_cast<HashTable>(NULL), tab);
  ASSERT_EQ(NumElementsInHashTable(tab), 91U);
  HW2Addpoints(10);

  // Do a few spot checks.
  {
    // article: 154, 170; identical: 918; versions: 499, 550, 653.
    const char *w1 = "article", *w2 = "identical", *w3 = "versions";
    HTKeyValue kv;
    int retval;
    WordPositions *wp;
    LLPayload_t pos;

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) w1, strlen(w1)),
                             &kv);
    ASSERT_EQ(retval, 1);
    wp = static_cast<WordPositions *>(kv.value);
    ASSERT_EQ(strcmp(w1, wp->word), 0);
    ASSERT_EQ(NumElementsInLinkedList(wp->positions), 2U);
    retval = PopLinkedList(wp->positions, &pos);
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, reinterpret_cast<LLPayload_t>(154U));
    retval = PopLinkedList(wp->positions, &pos);
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, reinterpret_cast<LLPayload_t>(170U));
    HW2Addpoints(10);

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) w2, strlen(w2)),
                             &kv);
    ASSERT_EQ(retval, 1);
    wp = static_cast<WordPositions *>(kv.value);
    ASSERT_EQ(strcmp(w2, wp->word), 0);
    ASSERT_EQ(NumElementsInLinkedList(wp->positions), 1U);
    retval = PopLinkedList(wp->positions, &pos);
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, reinterpret_cast<LLPayload_t>(918U));
    HW2Addpoints(10);

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) w3, strlen(w3)),
                             &kv);
    ASSERT_EQ(retval, 1);
    wp = static_cast<WordPositions *>(kv.value);
    ASSERT_EQ(strcmp(w3, wp->word), 0);
    ASSERT_EQ(NumElementsInLinkedList(wp->positions), 3U);
    retval = PopLinkedList(wp->positions, &pos);
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, reinterpret_cast<LLPayload_t>(499U));
    retval = PopLinkedList(wp->positions, &pos);
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, reinterpret_cast<LLPayload_t>(550U));
    retval = PopLinkedList(wp->positions, &pos);
    ASSERT_EQ(retval, 1);
    ASSERT_EQ(pos, reinterpret_cast<LLPayload_t>(653U));
    HW2Addpoints(10);

    retval = LookupHashTable(tab,
                             FNVHash64((unsigned char *) "blah", 4),
                             &kv);
    ASSERT_EQ(retval, 0);
    HW2Addpoints(10);
  }

  FreeWordHT(tab);
  HW2Addpoints(10);
}

TEST_F(Test_FileParser, PTestBigBuildWordHT) {
  HashTable tab =
    BuildWordHT(const_cast<char *>("./test_tree/books/paradiselost.txt"));
  ASSERT_NE(static_cast<HashTable>(NULL), tab);
  ASSERT_EQ(NumElementsInHashTable(tab), 10123U);
  FreeWordHT(tab);
  HW2Addpoints(10);
}

}  // namespace hw2
