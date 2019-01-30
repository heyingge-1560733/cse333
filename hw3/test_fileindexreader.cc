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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <string>

#include "./filelayout.h"
#include "./fileindexutil.h"
#include "./test_fileindexreader.h"
#include "./test_suite.h"

namespace hw3 {

TEST_F(Test_FileIndexReader, TestFileIndexReaderBasic) {
  // Open up the FILE * for ./unit_test_indices/enron.idx
  std::string idx("./unit_test_indices/enron.idx");
  FileIndexReader fir(idx);

  // Make sure the header fields line up correctly with the file size.
  struct stat f_stat;
  ASSERT_EQ(stat(idx.c_str(), &f_stat), 0);
  ASSERT_EQ((HWSize_t) f_stat.st_size,
            (HWSize_t) (get_doctable_size(&fir) +
                        get_index_size(&fir) +
                        sizeof(IndexFileHeader)));
  HW3Addpoints(10);

  // Manufacture a DocTableReader.
  DocTableReader dtr = fir.GetDocTableReader();

  // Try a lookup with it.
  std::string str;
  bool success = dtr.LookupDocID((DocID_t) 10, &str);
  ASSERT_TRUE(success);
  ASSERT_EQ(std::string("test_tree/enron_email/107."), str);

  // Done!.
  HW3Addpoints(20);
}

}  // namespace hw3
