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

#ifndef _HW2_FILECRAWLER_H
#define _HW2_FILECRAWLER_H

#include "memindex.h"
#include "doctable.h"

// CrawlFileTree crawls the file system subtree rooted at directory "rootdir".
// For each file that it encounters, it scans the file to test whether it
// contains ASCII text data.  If so, it indexes the file.
//
// Arguments:
//
// - rootdir: the directory that should serve as the root of the crawl.
//
// Returns:
//
// - doctable: an output parameter through which a DocTable is returned.
//   All indexed files are represented in the DocTable.
//
// - index: an output parameter through which an inverted index (i.e.,
//   a MemIndex) is returned.  All indexed files are represented in
//   the inverted index.
//
// - returns 0 on failure (nothing is allocated), 1 on success.
int CrawlFileTree(char *rootdir, DocTable *doctable, MemIndex *index);

#endif  // _HW2_FILECRAWLER_H
