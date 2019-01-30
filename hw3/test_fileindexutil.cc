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

#include "./test_fileindexutil.h"
#include "./fileindexutil.h"
#include "./test_suite.h"

namespace hw3 {

// This is the unit test for the 32-bit CRC calculation.
TEST_F(Test_FileIndexUtil, TestCRC32) {
  CRC32 crc;

  // Calculate the CRC of (0x01, 0x02, 0x03, 0x04).  It should be
  // the 32-bit unsigned number 0xB63CFBCD.
  crc.FoldByteIntoCRC((const uint8_t) 1);
  crc.FoldByteIntoCRC((const uint8_t) 2);
  crc.FoldByteIntoCRC((const uint8_t) 3);
  crc.FoldByteIntoCRC((const uint8_t) 4);
  ASSERT_EQ(((uint32_t) 0xB63CFBCD), crc.GetFinalCRC());
}

// This is the unit test for the htonll and ntohll macros.
TEST_F(Test_FileIndexUtil, TestHtonll) {
  uint64_t small = 0x01ULL;
  uint64_t medium = 0xFEDCBA98ULL;
  uint64_t large = 0x0100000000000000ULL;
  uint64_t giant = 0xFEDCBA9876543210ULL;
  uint64_t small_no, medium_no, large_no, giant_no;
  unsigned char *t;

  // Convert numbers to network order (i.e., big endian).
  small_no = htonll(small);
  medium_no = htonll(medium);
  large_no = htonll(large);
  giant_no = htonll(giant);

  // Verify they are in network order.
  t = (unsigned char *) &small_no;
  ASSERT_EQ((unsigned char) 0x00, t[0]);
  ASSERT_EQ((unsigned char) 0x00, t[1]);
  ASSERT_EQ((unsigned char) 0x00, t[6]);
  ASSERT_EQ((unsigned char) 0x01, t[7]);

  t = (unsigned char *) &medium_no;
  ASSERT_EQ((unsigned char) 0x00, t[0]);
  ASSERT_EQ((unsigned char) 0x00, t[1]);
  ASSERT_EQ((unsigned char) 0xBA, t[6]);
  ASSERT_EQ((unsigned char) 0x98, t[7]);

  t = (unsigned char *) &large_no;
  ASSERT_EQ((unsigned char) 0x01, t[0]);
  ASSERT_EQ((unsigned char) 0x00, t[1]);
  ASSERT_EQ((unsigned char) 0x00, t[6]);
  ASSERT_EQ((unsigned char) 0x00, t[7]);

  t = (unsigned char *) &giant_no;
  ASSERT_EQ((unsigned char) 0xFE, t[0]);
  ASSERT_EQ((unsigned char) 0xDC, t[1]);
  ASSERT_EQ((unsigned char) 0x32, t[6]);
  ASSERT_EQ((unsigned char) 0x10, t[7]);

  // Convert back to host order.
  small_no = htonll(small_no);
  medium_no = htonll(medium_no);
  large_no = htonll(large_no);
  giant_no = htonll(giant_no);

  // Ensure the conversion back to host order worked.
  ASSERT_EQ(small, small_no);
  ASSERT_EQ(medium, medium_no);
  ASSERT_EQ(large, large_no);
  ASSERT_EQ(giant, giant_no);
}

}  // namespace hw3
