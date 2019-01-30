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

#include "./test_suite.h"
#include "./test_filereader.h"

#include "./FileReader.h"

using std::string;

namespace hw4 {

TEST_F(Test_FileReader, TestFileReaderBasic) {
  // See if we can read a file successfully.
  FileReader f(".", "test_files/hextext.txt");
  std::string contents;
  ASSERT_TRUE(f.ReadFile(&contents));
  ASSERT_EQ(4800U, contents.size());
  HW4Addpoints(10);

  // Make sure reading a non-existent file fails.
  f = FileReader(".", "non-existent");
  ASSERT_FALSE(f.ReadFile(&contents));
  HW4Addpoints(5);

  // Make sure a file path attack fails.
  f = FileReader("./libhw2", "./libhw2/../cpplint.py");
  ASSERT_FALSE(f.ReadFile(&contents));
  HW4Addpoints(5);
}

}  // namespace hw4
