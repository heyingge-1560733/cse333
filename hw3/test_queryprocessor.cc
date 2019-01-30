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

#include <list>
#include <vector>
#include <string>

#include "./test_queryprocessor.h"
#include "./test_suite.h"

using std::list;
using std::vector;
using std::string;

namespace hw3 {

TEST_F(Test_QueryProcessor, TestQueryProcessorBasic) {
  // Set up the list of index files.
  list<string> idxlist;
  idxlist.push_back("./unit_test_indices/bash.idx");
  idxlist.push_back("./unit_test_indices/books.idx");
  idxlist.push_back("./unit_test_indices/enron.idx");

  // Construct the QueryProcessor.
  QueryProcessor qp(idxlist);

  // Try some queries.
  vector<string> query;
  query.push_back("whale");
  query.push_back("ocean");
  query.push_back("ravenous");

  vector<QueryProcessor::QueryResult> res = qp.ProcessQuery(query);
  ASSERT_EQ((unsigned int) 3, res.size());
  ASSERT_EQ(string("test_tree/books/mobydick.txt"), res[0].document_name);
  ASSERT_EQ((unsigned int) 1314, res[0].rank);
  ASSERT_EQ(string("test_tree/books/leavesofgrass.txt"),
            res[1].document_name);
  ASSERT_EQ((unsigned int) 42, res[1].rank);
  ASSERT_EQ(string("test_tree/books/ulysses.txt"), res[2].document_name);
  ASSERT_EQ((unsigned int) 15, res[2].rank);

  query.push_back("huckleberry");
  res = qp.ProcessQuery(query);
  ASSERT_EQ((unsigned int) 0, res.size());

  // Done!
  HW3Addpoints(20);
}

}  // namespace hw3
