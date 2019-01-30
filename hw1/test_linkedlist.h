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

#ifndef _HW1_TEST_LINKEDLIST_H_
#define _HW1_TEST_LINKEDLIST_H_

#include "./CSE333.h"
#include "gtest/gtest.h"

namespace hw1 {

class Test_LinkedList : public ::testing::Test {
 protected:
  Test_LinkedList() {
    // Do set-up work for each test here.
  }

  virtual ~Test_LinkedList() {
    // Do clean-up work for each test here.
  }

  virtual void SetUp() {
    // Code here will be called after the constructor and
    // right before each test.
  }

  virtual void TearDown() {
    // Code here will be called after each test and
    // right before the destructor.

    // Verify that none of the tests modifies any of the
    // testing constants.
    EXPECT_EQ((LLPayload_t)1U, kOne);
    EXPECT_EQ((LLPayload_t)2U, kTwo);
    EXPECT_EQ((LLPayload_t)3U, kThree);
    EXPECT_EQ((LLPayload_t)4U, kFour);
    EXPECT_EQ((LLPayload_t)5U, kFive);
  }

  static void SetUpTestCase() {
    // Code here will be called once for the entire
    // text fixture.  Note it is a static member function
    // (i.e., a class method, not an object instance method).
  }

  static void TearDownTestCase() {
    // Code here will be called once for the entire
    // text fixture.  Note it is a static member function
    // (i.e., a class method, not an object instance method).
  }

  // Objects declared here can be used by all tests in
  // the test case.

  // These values are used as payloads for the LinkedList tests.
  // They cannot be const, as stored value pointers are non-const.
  static LLPayload_t kOne, kTwo, kThree, kFour, kFive;
};  // class Test_LinkedList

}  // namespace hw1

#endif  // _HW1_TEST_LINKEDLIST_H_
