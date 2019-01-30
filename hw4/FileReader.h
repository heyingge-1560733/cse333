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

#ifndef _HW4_FILEREADER_H_
#define _HW4_FILEREADER_H_

#include <string>

namespace hw4 {

// This class is used to read a file into memory and return its
// contents as a string.
class FileReader {
 public:
  // "basedir" is the directory inside of which we will look for
  // files, and "fname" is a filename relative to that directory.
  // For example, if:
  //
  //   basedir is   "./hw4_htmldir"
  //   fname is     "test/foo.html"
  //
  // then we would read in "./hw4_htmldir/test/foo.html"
  FileReader(std::string basedir, std::string fname)
    : basedir_(basedir), fname_(fname) { }
  virtual ~FileReader(void) { }

  // Attempts to reads in the file specified by the constructor
  // arguments. If the file could not be found, could not be opened,
  // or exists above the basedir in the file system hierarchy (e.g.,
  // filename is "../../../escape.html"), returns false.  Otherwise,
  // returns true and also returns the file contents through "str".
  bool ReadFile(std::string *str);

 private:
  std::string basedir_;
  std::string fname_;
};

}  // namespace hw4

#endif  // _HW4_FILEREADER_H_
