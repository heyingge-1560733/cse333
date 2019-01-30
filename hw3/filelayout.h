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

#ifndef _HW3_FILELAYOUT_H_
#define _HW3_FILELAYOUT_H_

#include <stdint.h>
#include <cstddef>

extern "C" {
  #include "./libhw1/CSE333.h"
  #include "./libhw2/memindex.h"
}
#include "./fileindexutil.h"

// This header file defines templates (structs) for the
// hw3 on-disk data structures.  The templates make it 
// more convenient and efficient to read/write the files.

// C/C++ will add padding to structures to place the individual
// fields on their natural byte alignment.  That can lead to
// trouble -- the file must be read using the same structures as
// were used to write it.  Because that's so fragile, we 
// turn off padding on the structures defined here:

#pragma pack(push,1)

namespace hw3 {

//---------------------------------------------
// General types for encoded data on disk
//---------------------------------------------

  // An offset within an index file.
  typedef uint32_t IndexFileOffset_t;

//---------------------------------------------
// Index file header
//---------------------------------------------

typedef struct index_header_st {
  uint32_t   magic_number;
  uint32_t   checksum;
  HWSize_t   doctable_size;
  HWSize_t   index_size;

  void toDiskFormat() { magic_number = htonl(magic_number);
                        checksum = htonl(checksum);
                        doctable_size = htonl(doctable_size);
                        index_size = htonl(index_size);
                      }
  void toHostFormat() { magic_number = ntohl(magic_number);
                        checksum = ntohl(checksum);
                        doctable_size = ntohl(doctable_size);
                        index_size = ntohl(index_size);
                      } 
} IndexFileHeader;

// offset of magic number within an IndexFileHeader struct
#define MAGIC_NUMBER_OFFSET offsetof(IndexFileHeader, magic_number)
// offset of the doctable size field within an IndexFileHeader struct
#define DTSIZE_OFFSET offsetof(IndexFileHeader, doctable_size)

//---------------------------------------------
// Bucket list header
//  (Used by doctable, index, and docID table)
//---------------------------------------------

typedef struct bucket_list_header_st {
  HWSize_t   num_buckets;

  void toDiskFormat(){ num_buckets = htonl(num_buckets); }
  void toHostFormat(){ num_buckets = ntohl(num_buckets); }
} BucketListHeader;

typedef struct bucket_rec_st {
  HWSize_t           chain_len;
  IndexFileOffset_t  bucket_position;

  void toDiskFormat(){ chain_len = htonl(chain_len); bucket_position = htonl(bucket_position); }
  void toHostFormat(){ chain_len= ntohl(chain_len); bucket_position = ntohl(bucket_position); }
} bucket_rec;

typedef struct element_position_rec_st {
  IndexFileOffset_t  element_position;

  void toDiskFormat(){ element_position  = htonl(element_position); }
  void toHostFormat(){ element_position = ntohl(element_position); }
} element_position_rec;

//---------------------------------------------
// doctable element 
//---------------------------------------------

typedef struct doctable_element_header_st {
  DocID_t  docid;
  uint16_t  filename_len;  // Note: 16-bit quantity!

  void toDiskFormat(){ docid = htonll(docid); filename_len = htons(filename_len); }
  void toHostFormat(){ docid = ntohll(docid); filename_len = ntohs(filename_len); }
} doctable_element_header;

//---------------------------------------------
// Word doc set 
//---------------------------------------------

typedef struct worddocset_header_st {
  uint16_t   word_len;  // Note: 16-bit quantity!
  HWSize_t   doctable_len;

  void toDiskFormat() { word_len = htons(word_len); doctable_len = htonl(doctable_len); }
  void toHostFormat() { word_len = ntohs(word_len); doctable_len = ntohl(doctable_len); }
} worddocset_header;

//---------------------------------------------
// DocID element 
//---------------------------------------------

typedef struct docid_element_header_st {
  DocID_t  docid;
  HWSize_t  num_positions;

  void toDiskFormat(){ docid = htonll(docid); num_positions = htonl(num_positions); }
  void toHostFormat(){ docid = ntohll(docid); num_positions = ntohl(num_positions); }
} docid_element_header;

typedef struct docid_element_position_st {
  DocPositionOffset_t position;

  void toDiskFormat() { position = htonl(position); }
  void toHostFormat() { position = ntohl(position); }
} docid_element_position;


}  // namespace hw3

#pragma pack(pop)

#endif  // _HW3_FILELAYOUT_H_
