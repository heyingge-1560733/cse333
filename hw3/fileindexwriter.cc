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

#include <cstdio>    // for (FILE *).
#include <cstring>   // for strlen(), etc.

#include "./filelayout.h"
#include "./fileindexutil.h"  // for many useful routines!
#include "./fileindexwriter.h"

// We need to peek inside the implementation of a HashTable so
// that we can iterate through its buckets and their chain elements.
extern "C" {
  #include "libhw1/CSE333.h"
  #include "libhw1/HashTable_priv.h"
}

namespace hw3 {

// Helper function to write the docid->filename mapping from the
// DocTable "dt" into file "f", starting at byte offset "offset".
// Returns the size of the written DocTable or 0 on error.
static HWSize_t WriteDocTable(FILE *f, DocTable dt, IndexFileOffset_t offset);

// Helper function to write the MemIndex "mi" into file "f", starting
// at byte offset "offset."  Returns the size of the written MemIndex
// or 0 on error.
static HWSize_t WriteMemIndex(FILE *f, MemIndex mi, IndexFileOffset_t offset);

// Helper function to write the index file's header into file "f".
// Returns the number of header bytes written on success, 0 on
// failure.  Will atomically write the MAGIC_NUMBER as the very last
// thing; as a result, if we crash part way through writing an index
// file, it won't contain a valid MAGIC_NUMBER and the rest of HW3
// will know to report an error.
static HWSize_t WriteHeader(FILE *f,
                            HWSize_t doct_size,
                            HWSize_t memidx_size);

// A write_element_fn is used by WriteHashTable() to write a
// HashTable's HTKeyValue element into the index file at offset
// "offset".
//
// Returns the number of bytes written or 0 on error.
typedef HWSize_t (*write_element_fn)(FILE *f,
                                     IndexFileOffset_t offset,
                                     HTKeyValue *kv);

// Helper function to write a HashTable into file "f", starting at
// offset "offset".  The helper function "write_element_fn" is invoked
// to writes each HTKeyValue element within the HashTable into the
// file.
//
// Returns the total amount of data written, or 0 on failure.
static HWSize_t WriteHashTable(FILE *f,
                               HashTable t,
                               IndexFileOffset_t offset,
                               write_element_fn fn);

// Helper function used by WriteHashTable() to write out a bucket
// record (i.e., a "bucket_rec" within the hw3 diagrams).  Returns the
// amount of data written, or 0 on failure.
//
// "f" is the file to write into, "li" is the bucket chain linked
// list, "br_offset" is the offset of the 'bucket_rec' field to write
// into, and "b_offset" is the value of 'bucket offset' field to write
// within the bucket_rec field.
static HWSize_t WriteBucketRecord(FILE *f,
                                  LinkedList li,
                                  IndexFileOffset_t br_offset,
                                  IndexFileOffset_t b_offset);

// Helper function used by WriteHashTable() to write out a bucket.
// Returns the amount of data written, or 0 on failure.
//
// "f" is the file to write into, "li" is the bucket chain linked list
// to write within the bucket, 'offset' is the offset of the bucket,
// and 'write_element_fn' is a helper function used to write the
// HTKeyValue into the element itself.
static HWSize_t WriteBucket(FILE *f,
                            LinkedList li,
                            IndexFileOffset_t offset,
                            write_element_fn fn);

HWSize_t WriteIndex(MemIndex mi, DocTable dt, const char *filename) {
  HWSize_t filesize = 0, dtres, mires, hdres;
  FILE *f;

  // Do some sanity checking on the arguments we were given.
  Verify333(mi != nullptr);
  Verify333(dt != nullptr);
  Verify333(filename != nullptr);

  // fopen() the file for writing; use mode "wb+" to indicate binary,
  // write mode, and to create/truncate the file.
  f = fopen(filename, "wb+");
  if (f == nullptr)
    return 0;

  // write the document table using WriteDocTable().
  dtres = WriteDocTable(f, dt, sizeof(IndexFileHeader));
  if (dtres == 0) {
    fclose(f);
    unlink(filename);
    return 0;
  }
  filesize += dtres;

  // write the memindex using WriteMemIndex().
  // MISSING:
  mires = WriteMemIndex(f, mi, sizeof(IndexFileHeader) + filesize);
  if (mires == 0) {
    fclose(f);
    unlink(filename);
    return 0;
  }
  filesize += mires;

  // write the header using WriteHeader().
  // MISSING:
  hdres = WriteHeader(f, dtres, mires);
  if (hdres == 0) {
    fclose(f);
    unlink(filename);
    return 0;
  }
  filesize += hdres;

  // Clean up and return the total amount written.
  fclose(f);
  return filesize;
}

// This write_element_fn is used to write a docid->docname mapping
// element, i.e., an element of the "doctable" table.
static HWSize_t WriteDocidDocnameFn(FILE *f,
                                    IndexFileOffset_t offset,
                                    HTKeyValue *kv) {
  size_t res;
  uint16_t slen_ho;

  // determine the filename length
  // MISSING (change this assignment to the correct thing):
  slen_ho = strlen(static_cast<char *>(kv->value));

  // fwrite() the docid from "kv".  Remember to convert to
  // disk format before writing.
  doctable_element_header header = {kv->key, slen_ho};
  header.toDiskFormat();

  // fseek() to the provided offset and then write the header.
  if (fseek(f, offset, SEEK_SET) != 0)
    return 0;
  res = fwrite(&header, sizeof(header), 1, f);
  if (res != 1)
    return 0;

  // fwrite() the filename.  We don't write the null-terminator from
  // the string, just the characters.
  // MISSING:
  if (fseek(f, offset + sizeof(header), SEEK_SET) != 0)
    return 0;
  res = fwrite(static_cast<void *>(kv->value), slen_ho, 1, f);
  if (res != 1)
    return 0;

  // calculate and return the total amount written.
  // MISSING (change this return to the correct thing):
  return sizeof(header) + slen_ho;
}

static HWSize_t WriteDocTable(FILE *f, DocTable dt, IndexFileOffset_t offset) {
  // Use WriteHashTable() to write the docid->filename hash table.
  // You'll need to use DTGetDocidTable() to get the docID hash table
  // from dt, and you'll need to pass in WriteDocidDocnameFn as the
  // final parameter of WriteHashTable().
  return WriteHashTable(f,
                        DTGetDocidTable(dt),
                        offset,
                        &WriteDocidDocnameFn);
}

// This write_element_fn is used to write a DocID + position list
// element (i.e., an element of a nested docID table) into the file at
// offset 'offset'.
static HWSize_t WriteDocPositionListFn(FILE *f,
                                       IndexFileOffset_t offset,
                                       HTKeyValue *kv) {
  size_t res;
  HWSize_t total = 0;

  // Extract the docID from the HTKeyValue.
  DocID_t docID_ho = (DocID_t)kv->key;

  // Extract the positions LinkedList from the HTKeyValue and
  // determine its size.
  LinkedList positions = (LinkedList)kv->value;
  HWSize_t num_pos_ho = NumElementsInLinkedList(positions);

  // Write the header, in disk format.
  // You'll need to fseek() to the right location in the file.
  // MISSING:
  docid_element_header header = {docID_ho, num_pos_ho};
  header.toDiskFormat();

  // fseek() to the provided offset and then write the header.
  res = fseek(f, offset, SEEK_SET);
  if (res != 0)
    return 0;
  res = fwrite(&header, sizeof(header), 1, f);
  if (res != 1)
    return 0;

  // update amount of data written
  total += sizeof(header);

  // Loop through the positions list, writing each position out.
  docid_element_position position;
  LLIter it = LLMakeIterator(positions, 0);
  Verify333(it != nullptr);
  for (HWSize_t i = 0; i < num_pos_ho; i++) {
    // Get the next position from the list.
    // MISSING:
    LLPayload_t payload;
    LLIteratorGetPayload(it, reinterpret_cast<void **>(&payload));

    // Truncate to 32 bits, then convert it to network order and write it out.
    // MISSING:
    position.position = *reinterpret_cast<uint32_t*>(&payload);
    position.toDiskFormat();

    // fseek() to the provided offset and then write the header.
    res = fseek(f, offset + total, SEEK_SET);
    if (res != 0) {
      LLIteratorFree(it);  // free iterator
      return 0;
    }
    res = fwrite(&position, sizeof(position), 1, f);
    if (res != 1) {
      LLIteratorFree(it);  // free iterator
      return 0;
    }

    // update amount of data written
    total += sizeof(position);
    // Iterate to the next position.
    LLIteratorNext(it);
  }
  LLIteratorFree(it);  // free iterator

  // Calculate and return the total amount of data written.
  // MISSING (fix this return value):
  return total;
}

// This write_element_fn is used to write a WordDocSet
// element into the file at position 'offset'.
static HWSize_t WriteWordDocSetFn(FILE *f,
                                  IndexFileOffset_t offset,
                                  HTKeyValue *kv) {
  size_t res;

  // Extract the WordDocSet from the HTKeyValue.
  WordDocSet *wds = static_cast<WordDocSet *>(kv->value);
  Verify333(wds != nullptr);

  // Prepare the wordlen field.
  uint16_t wordlen_ho;
  // MISSING:
  wordlen_ho = strlen(wds->word);

  // Write the nested DocID->positions hashtable (i.e., the "docID
  // table" element in the diagrams).  Use WriteHashTable() to do it,
  // passing it the wds->docIDs table and using the
  // WriteDocPositionListFn helper function as the final parameter.
  HWSize_t htlen_ho = WriteHashTable
                      (f, wds->docIDs,
                       offset + sizeof(worddocset_header) + wordlen_ho,
                       &WriteDocPositionListFn);
  if (htlen_ho == 0)
    return 0;

  // Write the header, in network order, in the right
  // place in the file.
  worddocset_header header = {wordlen_ho, htlen_ho};
  // MISSING:
  header.toDiskFormat();

  // fseek() to the provided offset and then write the header.
  if (fseek(f, offset, SEEK_SET) != 0)
    return 0;
  res = fwrite(&header, sizeof(header), 1, f);
  if (res != 1)
    return 0;

  // Write the word itself, excluding the nullptr terminator,
  // in the right place in the file.
  // MISSING:
  if (fseek(f, offset + sizeof(worddocset_header), SEEK_SET) != 0)
    return 0;
  res = fwrite(wds->word, wordlen_ho, 1, f);
  if (res != 1)
    return 0;

  // Calculate and return the total amount of data written.
  // MISSING (fix this return value):
  return sizeof(worddocset_header) + wordlen_ho + htlen_ho;
}

static HWSize_t WriteMemIndex(FILE *f, MemIndex mi, IndexFileOffset_t offset) {
  // Use WriteHashTable() to write the MemIndex into the file.  You'll
  // need to pass in the WriteWordDocSetFn helper function as the
  // final argument.
  return WriteHashTable(f,
                        mi,
                        offset,
                        &WriteWordDocSetFn);
}

static HWSize_t WriteHeader(FILE *f,
                            HWSize_t doct_size,
                            HWSize_t memidx_size) {
  // We need to calculate the checksum over the doctable and index
  // table.  (Note that the checksum does not include the index file
  // header, just these two tables.)  Use fseek() to seek to the right
  // location, and use a CRC32 object from fileindexutil.h to do the
  // CRC checksum calculation, feeding it characters that you read
  // from the index file using fread().

  IndexFileHeader header = {MAGIC_NUMBER, 0, doct_size, memidx_size};

  HWSize_t cslen = doct_size + memidx_size;
  CRC32 crcobj;

  // MISSING:
  HWSize_t res = fseek(f, sizeof(header), SEEK_SET);
  if (res != 0)
    return 0;
  uint8_t nextbyte;

  // repeatedly fold bytes into CRC object
  for (HWSize_t i = 0; i < cslen; i++) {
    if (fseek(f, sizeof(header) + i, SEEK_SET) != 0)
      return 0;
    if (fread(reinterpret_cast<void *>(&nextbyte),
        sizeof(nextbyte), 1, f) != 1)
      return 0;
    crcobj.FoldByteIntoCRC(nextbyte);
  }

  header.checksum = crcobj.GetFinalCRC();  // update checksum field
  crcobj.~CRC32();  // destruct the CRC32 object

  // Write the header fields.  Be sure to convert the fields to
  // network order before writing them!
  header.toDiskFormat();

  if (fseek(f, 0, SEEK_SET) != 0)
    return 0;
  if (fwrite(&header, sizeof(header), 1, f) != 1)
    return 0;

  // Use fsync to flush the header field to disk.
  Verify333(fsync(fileno(f)) == 0);

  // We're done!  Return the number of header bytes written.
  return sizeof(IndexFileHeader);
}

static HWSize_t WriteBucketRecord(FILE *f,
                                  LinkedList li,
                                  IndexFileOffset_t br_offset,
                                  IndexFileOffset_t b_offset) {
  HWSize_t res;

  // Use NumElementsInLinkedList() to figure out how many chained
  // elements are in this bucket.  Put bucket_rec in network
  // byte order.
  bucket_rec br;
  // MISSING:
  br.chain_len = NumElementsInLinkedList(li);
  br.bucket_position = b_offset;

  // fseek() to the "bucket_rec" record for this bucket.
  res = fseek(f, br_offset, SEEK_SET);
  if (res != 0)
    return 0;

  // Write the bucket_rec.
  // MISSING:
  br.toDiskFormat();
  res = fwrite(&br, sizeof(bucket_rec), 1, f);
  if (res != 1)
    return 0;

  // Calculate and return how many bytes we wrote.
  return sizeof(bucket_rec);
}

static HWSize_t WriteBucket(FILE *f,
                            LinkedList li,
                            IndexFileOffset_t offset,
                            write_element_fn fn) {
  // Use NumElementsInLinkedList() to calculate how many elements are
  // in this bucket chain.
  HWSize_t chainlen_ho = NumElementsInLinkedList(li);

  // "bucketlen" is our running calculation of how many bytes have
  // been written out for this bucket.
  HWSize_t bucketlen = sizeof(element_position_rec) * chainlen_ho;

  // Figure out the position of the next "element" in the bucket.
  HWSize_t nextelpos = offset + bucketlen;

  // Loop through the chain, writing each associated "element position"
  // header field for the bucket and then writing out the "element"
  // itself.  Be sure to write things in network order.  Use the
  // "fn" parameter to invoke the helper function that knows how to
  // write out the payload of each chain element into the "element"
  // fields of the bucket.
  if (chainlen_ho > 0) {
    LLIter it = LLMakeIterator(li, 0);
    Verify333(it != nullptr);
    HWSize_t j;
    for (j = 0; j < chainlen_ho; j++) {
      HWSize_t ellen, res;
      HTKeyValue *kv;

      // MISSING:
      // writing element position record
      element_position_rec el_pos = {nextelpos};
      el_pos.toDiskFormat();

      // fseek() to the provided offset and then write the header.
      if (fseek(f, offset + j * sizeof(element_position_rec), SEEK_SET) != 0) {
        LLIteratorFree(it);  // free iterator
        return 0;
      }
      res = fwrite(&el_pos, sizeof(element_position_rec), 1, f);
      if (res != 1) {
        LLIteratorFree(it);  // free iterator
        return 0;
      }

      // get value of the current payload
      LLIteratorGetPayload(it, reinterpret_cast<LLPayload_t *>(&kv));
      ellen = fn(f, nextelpos, kv);
      if (ellen == 0) {
        LLIteratorFree(it);  // free iterator
        return 0;
      }

      // Advance to the next element in the chain, tallying up our
      // lengths.
      bucketlen += ellen;
      nextelpos += ellen;
      LLIteratorNext(it);
    }
    LLIteratorFree(it);  // free iterator
  }

  // Return the total amount of data written.
  return bucketlen;
}

// This is the main workhorse of the file.  It iterates through the
// buckets in the HashTable "t", writing the hash table out into
// the index file.
static HWSize_t WriteHashTable(FILE *f,
                               HashTable t,
                               IndexFileOffset_t offset,
                               write_element_fn fn) {
  HashTableRecord *ht = static_cast<HashTableRecord *>(t);
  IndexFileOffset_t next_bucket_rec_offset = offset + sizeof(BucketListHeader);
  IndexFileOffset_t next_bucket_offset;
  HWSize_t i, res;

  // fwrite() out the "num_buckets" (number of buckets) field, in
  // network order.
  BucketListHeader header = {ht->num_buckets};
  header.toDiskFormat();
  res = fseek(f, offset, SEEK_SET);
  if (res != 0)
    return 0;
  res = fwrite(&header.num_buckets, sizeof(BucketListHeader), 1, f);
  if (res != 1)
    return 0;

  // Figure out the offset of the first "bucket" field.  Each
  // bucket_rec is sizeof(bucket_rec) bytes, and there
  // are ht->num_buckets of them.
  next_bucket_offset = next_bucket_rec_offset +
                         (ht->num_buckets) * sizeof(bucket_rec);

  // Loop through table's buckets, writing them out to the appropriate
  // "bucket_rec" and "bucket" fields within the file index.  Writing
  // a bucket means writing the bucket_rec, then writing the bucket
  // itself.  Use WriteBucketRecord() to write a bucket_rec, and
  // WriteBucket() to write a bucket.
  //
  // Be sure to handle the corner case where the bucket's chain is
  // empty.  For that case, you still have to write a "bucket_rec"
  // record for the bucket, but you won't write a "bucket".
  for (i = 0; i < ht->num_buckets; i++) {
    // MISSING:
    // writing the bucket_rec into file
    HWSize_t br_res = WriteBucketRecord(f, ht->buckets[i],
                                        next_bucket_rec_offset,
                                        next_bucket_offset);
    if (br_res == 0) {
      return 0;
    }
    Verify333(br_res == sizeof(bucket_rec));

    // writing the bucket into file
    if (NumElementsInLinkedList(ht->buckets[i]) != 0) {
      HWSize_t b_res = WriteBucket(f, ht->buckets[i], next_bucket_offset, fn);
      if (b_res == 0) {
        return 0;
      }
      // update next bucket offset
      next_bucket_offset += b_res;
    }

    // update next bucket record offset
    next_bucket_rec_offset += br_res;
  }

  // Calculate and return the total number of bytes written.
  return (next_bucket_offset - offset);
}

}  // namespace hw3
