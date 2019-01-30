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

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "./fileindexwriter.h"

extern "C" {
  #include "./libhw2/filecrawler.h"
  #include "./libhw2/doctable.h"
  #include "./libhw2/memindex.h"
}

void Usage(char *filename) {
  std::cerr << "Usage: " << filename;
  std::cerr << " crawlrootdir indexfilename" << std::endl;
  std::cerr << "where:" << std::endl;
  std::cerr << "  crawlrootdir is the name of a directory to crawl";
  std::cerr << std::endl;
  std::cerr << "  indexfilename is the name of the index file to create";
  std::cerr << std::endl;
  exit(EXIT_FAILURE);
}

// This program links together the HW2 CrawlFileTree() from
// filecrawler.c with the HW3 WriteIndexFile() from
// fileindexwrite.cc. Using them, the program crawls the file system
// subtree specified by argv[1], builds up an in-memory index, and then
// writes it out to the index file specified by argv[2].
int main(int argc, char **argv) {
  HWSize_t idxlen;
  DocTable dt;
  MemIndex idx;

  // Make sure the user provided us the right command-line options.
  if (argc != 3)
    Usage(argv[0]);

  // Try to crawl.
  std::cout << "Crawling " << argv[1] << "..." << std::endl;
  if (CrawlFileTree(argv[1], &dt, &idx) != 1)
    Usage(argv[0]);

  // Try to write out the index file.
  std::cout << "Writing index to " << argv[2];
  std::cout << "..." << std::endl;
  idxlen = hw3::WriteIndex(idx, dt, argv[2]);
  if (idxlen == 0) {
    FreeDocTable(dt);
    FreeMemIndex(idx);
    return EXIT_FAILURE;
  }

  // All done!  Clean up.
  std::cout << "Done. Cleaning up memory." << std::endl;
  FreeDocTable(dt);
  FreeMemIndex(idx);
  return EXIT_SUCCESS;
}
