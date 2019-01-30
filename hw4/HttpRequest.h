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

#ifndef _HW4_HTTPREQUEST_H_
#define _HW4_HTTPREQUEST_H_

#include <stdint.h>

#include <map>
#include <string>

using std::string;

namespace hw4 {

// This class represents the state of an HTTP request.  We'll
// only handle "GET"-style requests in this project, which means
// a request has the following format:
//
// GET [URI] [http_protocol]\r\n
// [headername]: [headerval]\r\n
// [headername]: [headerval]\r\n
// ... more headers ...
// [headername]: [headerval]\r\n
// \r\n
//
// e.g.:
//
// GET /foo/bar?baz=bam HTTP/1.1\r\n
// Host: www.news.com\r\n
//
class HttpRequest {
 public:
  HttpRequest() { }
  virtual ~HttpRequest(void) { }

  // Which URI did the client request?
  std::string URI;

  // A map from header name to header value, representing
  // all of the headers that the client supplied to us.  The
  // header names are converted to all lower case; the header
  // values are retained verbatim.
  std::map<std::string, std::string> headers;
};

}  // namespace hw4

#endif  // _HW4_HTTPREQUEST_H_
